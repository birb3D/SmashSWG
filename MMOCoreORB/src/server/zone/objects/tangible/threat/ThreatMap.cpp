/*
 * DamageMap.cpp
 *
 *  Created on: 13/07/2010
 *      Author: victor
 */

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"
#include "ThreatMap.h"
#include "ThreatStates.h"
#include "server/zone/objects/tangible/tasks/ClearThreatStateTask.h"
#include "server/zone/objects/tangible/tasks/RemoveAggroTask.h"
#include "server/zone/objects/group/GroupObject.h"
#include "ThreatMapClearObserversTask.h"
#include "server/zone/Zone.h"

void ThreatMapEntry::addDamage(WeaponObject* weapon, uint32 damage) {
	addDamage(weapon->getXpType(), damage);
}

void ThreatMapEntry::addDamage(String xp, uint32 damage) {
	int idx = find(xp);

	if (idx == -1) {
		put(xp, damage);

	} else {
		uint32* dmg = &elementAt(idx).getValue();

		*dmg = *dmg + damage;
	}
}

void ThreatMapEntry::setThreatState(uint64 state) {
	if (!(threatBitmask & state))
		threatBitmask |= state;
}

bool ThreatMapEntry::hasState(uint64 state) {
	if (threatBitmask & state)
		return true;

	return false;
}

void ThreatMapEntry::clearThreatState(uint64 state) {
	if (threatBitmask & state)
		threatBitmask &= ~state;
}

void ThreatMap::registerObserver(TangibleObject* target) {
	if (threatMapObserver == nullptr) {
		threatMapObserver = new ThreatMapObserver(self.get());
		threatMapObserver->deploy();
	}

	target->registerObserver(ObserverEventType::HEALINGRECEIVED, threatMapObserver);
}

void ThreatMap::removeObservers() {
	if (size() == 0)
		return;

	Reference<ThreatMapClearObserversTask*> task = new ThreatMapClearObserversTask(*this, threatMapObserver);
	Core::getTaskManager()->executeTask(task);
}

void ThreatMap::addDamage(TangibleObject* target, uint32 damage, String xp) {
	Locker locker(&lockMutex);

	ManagedReference<TangibleObject*> strongSelf = self.get();
	if (strongSelf == nullptr || strongSelf.get() == target)
		return;

	int idx = find(target);
	String xpToAward = "";

	if (xp == "" && target->isCreatureObject()) {
		CreatureObject* tarCreo = target->asCreatureObject();

		if (tarCreo != nullptr) {
			WeaponObject* weapon = tarCreo->getWeapon();

			if (weapon != nullptr)
				xpToAward = weapon->getXpType();
		}
	} else {
		xpToAward = xp;
	}

	if (idx == -1) {
		ThreatMapEntry entry;
		entry.addDamage(xpToAward, damage);
		entry.addAggro(damage);

		put(target, entry);
		registerObserver(target);

	} else {
		ThreatMapEntry* entry = &elementAt(idx).getValue();
		entry->addDamage(xpToAward, damage);
		entry->addAggro(damage);
	}
}

void ThreatMap::removeAll(bool forceRemoveAll) {
	Locker locker(&lockMutex);

	removeObservers();

	for (int i = size() - 1; i >= 0; i--) {
		VectorMapEntry<ManagedReference<TangibleObject*>, ThreatMapEntry>* entry = &elementAt(i);

		ManagedReference<TangibleObject*> key = entry->getKey();
		ThreatMapEntry* value = &entry->getValue();

		ManagedReference<TangibleObject*> selfStrong = self.get();

		// these checks will determine if we should store the damage from the dropped aggressor
		Zone* keyZone = (key != nullptr ? key->getZone() : nullptr);
		Zone* selfZone = (selfStrong != nullptr ? selfStrong->getZone() : nullptr);

		uint32 keyPlanetCRC = (keyZone != nullptr ? keyZone->getPlanetCRC() : 0);
		uint32 selfPlanetCRC = (selfZone != nullptr ? selfZone->getPlanetCRC() : 0);

		if (key == nullptr || selfStrong == nullptr || keyPlanetCRC != selfPlanetCRC || forceRemoveAll || (key->isCreatureObject() && (key->asCreatureObject()->isDead() || !key->asCreatureObject()->isOnline()))) {
			remove(i);

			if (threatMapObserver != nullptr) {
				key->dropObserver(ObserverEventType::HEALINGRECEIVED, threatMapObserver);
			}
		} else {
			value->setNonAggroDamage(value->getTotalDamage());
			value->addHeal(-value->getHeal()); // don't need to store healing
			value->clearAggro();
		}
	}

	currentThreat = nullptr;
	threatMatrix.clear();
}

void ThreatMap::dropDamage(TangibleObject* target) {
	Locker llocker(&lockMutex);

	ManagedReference<TangibleObject*> selfStrong = self.get();

	if (target == nullptr || selfStrong == nullptr || target->getPlanetCRC() != selfStrong->getPlanetCRC() || (target->isCreatureObject() && (target->asCreatureObject()->isDead() || !target->asCreatureObject()->isOnline()))) {
		drop(target);

		if (threatMapObserver != nullptr) {
			target->dropObserver(ObserverEventType::HEALINGRECEIVED, threatMapObserver);
		}
	} else {
		ThreatMapEntry* entry = &get(target);
		entry->setNonAggroDamage(entry->getTotalDamage());
		entry->addHeal(-entry->getHeal()); // don't need to store healing
		entry->clearAggro();
	}

	llocker.release();

	if (currentThreat == target)
		currentThreat = nullptr;
}

bool ThreatMap::setThreatState(TangibleObject* target, uint64 state, uint64 duration, uint64 cooldown) {
	Locker locker(&lockMutex);

	if ((hasState(state) && isUniqueState(state)) || !cooldownTimerMap.isPast(String::valueOf(state)))
		return false;

	int idx = find(target);

	if (idx == -1) {
		ThreatMapEntry entry;
		entry.setThreatState(state);
		put(target, entry);
		registerObserver(target);

	} else {
		ThreatMapEntry* entry = &elementAt(idx).getValue();
		entry->setThreatState(state);
	}

	if (duration > 0) {
		Reference<ClearThreatStateTask*> clearThreat = new ClearThreatStateTask(self.get(), target, state);
		clearThreat->schedule(duration);
	}

	if (cooldown > 0) {
		cooldownTimerMap.updateToCurrentAndAddMili(String::valueOf(state), duration + cooldown);
	}

	if (isUniqueState(state)) {
		cooldownTimerMap.updateToCurrentTime("doEvaluation");
	}

#ifdef DEBUG
	System::out << "Setting threat state on " << target->getObjectID() << ": " << state << endl;
#endif

	return true;
}

bool ThreatMap::hasState(uint64 state) {
	Locker locker(&lockMutex);

	for (int i = 0; i < size(); ++i) {
		ThreatMapEntry* entry = &elementAt(i).getValue();
		if (entry->hasState(state))
			return true;
	}

	return false;
}

bool ThreatMap::isUniqueState(uint64 state) {
	return state & ThreatStates::UNIQUESTATE;
}

void ThreatMap::clearThreatState(TangibleObject* target, uint64 state) {
	Locker locker(&lockMutex);

	int idx = find(target);

	if (idx != -1) {
		ThreatMapEntry* entry = &elementAt(idx).getValue();
		entry->clearThreatState(state);

#ifdef DEBUG
		System::out << "Clearing threat state on " << target->getObjectID() << ": " << state << endl;
#endif
	}
}

uint32 ThreatMap::getTotalDamage() {
	Locker locker(&lockMutex);

	uint32 totalDamage = 0;

	for (int i = 0; i < size(); ++i) {
		ThreatMapEntry* entry = &elementAt(i).getValue();

		totalDamage += entry->getTotalDamage();
	}

	return totalDamage;
}

CreatureObject* ThreatMap::getHighestDamagePlayer() {
	Locker locker(&lockMutex);

	uint32 maxDamage = 0;
	VectorMap<uint64, uint32> damageMap;
	CreatureObject* player = nullptr;

	for (int i = 0; i < size(); ++i) {
		ThreatMapEntry* entry = &elementAt(i).getValue();

		uint32 totalDamage = entry->getTotalDamage();

		TangibleObject* tano = elementAt(i).getKey();

		if (tano == nullptr) {
			continue;
		}

		if (tano->isPlayerCreature()) {
			if (!damageMap.contains(tano->getObjectID())) {
				damageMap.put(tano->getObjectID(), totalDamage);
			} else {
				damageMap.get(tano->getObjectID()) += totalDamage;
			}

			if (damageMap.get(tano->getObjectID()) > maxDamage) {
				maxDamage = damageMap.get(tano->getObjectID());
				player = cast<CreatureObject*>(tano);
			}
		} else if (tano->isPet()) {
			CreatureObject* creo = tano->asCreatureObject();

			if (creo == nullptr) {
				continue;
			}

			CreatureObject* owner = creo->getLinkedCreature().get();

			if (owner != nullptr && owner->isPlayerCreature()) {
				if (!damageMap.contains(owner->getObjectID())) {
					damageMap.put(owner->getObjectID(), totalDamage);
				} else {
					damageMap.get(owner->getObjectID()) += totalDamage;
				}

				if (damageMap.get(owner->getObjectID()) > maxDamage) {
					maxDamage = damageMap.get(owner->getObjectID());
					player = cast<CreatureObject*>(owner);
				}
			}
		}
	}

	return player;
}

CreatureObject* ThreatMap::getHighestDamageGroupLeader() {
	Locker locker(&lockMutex);

	VectorMap<uint64, uint32> groupDamageMap;
	int64 highestGroupDmg = 0;

	// Logger::Logger tlog("Threat");

	ManagedReference<CreatureObject*> leaderCreature = nullptr;

	for (int i = 0; i < size(); ++i) {
		ThreatMapEntry* entry = &elementAt(i).getValue();

		uint32 totalDamage = entry->getLootDamage();

		TangibleObject* tano = elementAt(i).getKey();

		if (tano != nullptr && tano->isCreatureObject()) {
			CreatureObject* creature = tano->asCreatureObject();

			// tlog.info("Group id is " + String::valueOf(creature->getGroupID()),true);
			if (creature != nullptr && creature->isGrouped()) {
				Reference<CreatureObject*> thisleader = creature->getGroup()->getLeader();
				// tlog.info("leader is " + thisleader->getFirstName(),true);

				if (thisleader == nullptr || !thisleader->isPlayerCreature())
					break;

				if (!groupDamageMap.contains(creature->getGroupID())) {
					// tlog.info("first dmg for group " + String::valueOf(creature->getGroupID()) + " dmg: " + String::valueOf(totalDamage), true);
					groupDamageMap.put(creature->getGroupID(), totalDamage);

				} else {
					groupDamageMap.get(creature->getGroupID()) += totalDamage;
					// tlog.info("adding to group " + String::valueOf(creature->getGroupID()) + "  dmg total: " +
					// String::valueOf(groupDamageMap.get(creature->getGroupID())) + " this player dmg: " + String::valueOf(totalDamage),true);
				}

				if (groupDamageMap.get(creature->getGroupID()) > highestGroupDmg) {
					highestGroupDmg = groupDamageMap.get(creature->getGroupID());
					leaderCreature = thisleader;
				}
			} else if (creature->isPet()) {
				CreatureObject* owner = creature->getLinkedCreature().get();

				if (owner != nullptr && owner->isPlayerCreature()) {
					if (owner->isGrouped()) {
						Reference<CreatureObject*> thisleader = owner->getGroup()->getLeader();

						if (thisleader == nullptr || !thisleader->isPlayerCreature())
							break;

						if (!groupDamageMap.contains(owner->getGroupID())) {
							groupDamageMap.put(owner->getGroupID(), totalDamage);
						} else {
							groupDamageMap.get(owner->getGroupID()) += totalDamage;
						}

						if (groupDamageMap.get(owner->getGroupID()) > highestGroupDmg) {
							highestGroupDmg = groupDamageMap.get(owner->getGroupID());
							leaderCreature = thisleader;
						}
					} else {
						if (!groupDamageMap.contains(owner->getObjectID())) {
							groupDamageMap.put(owner->getObjectID(), totalDamage);
						} else {
							groupDamageMap.get(owner->getObjectID()) += totalDamage;
						}

						if (totalDamage > highestGroupDmg) {
							highestGroupDmg = totalDamage;
							leaderCreature = owner;
						}
					}
				}
			} else {
				// tlog.info("adding single creature damage " + String::valueOf(totalDamage),true);
				groupDamageMap.put(creature->getObjectID(), totalDamage);

				if (totalDamage > highestGroupDmg) {
					highestGroupDmg = totalDamage;
					leaderCreature = creature;
				}
			}
		}
	}
	// tlog.info("highest group is " + leaderCreature->getFirstName() + " damage of " + String::valueOf(highestGroupDmg),true);
	return leaderCreature;
}

TangibleObject* ThreatMap::getHighestThreatAttacker() {
	Locker locker(&lockMutex);

	ManagedReference<TangibleObject*> currentThreat = this->currentThreat.get();

	if (currentThreat != nullptr && !currentThreat->isDestroyed() && !cooldownTimerMap.isPast("doEvaluation")) {
		if (currentThreat->isCreatureObject()) {
			ManagedReference<CreatureObject*> currentCreo = currentThreat->asCreatureObject();

			if (currentCreo != nullptr && !currentCreo->isDead() && !currentCreo->isIncapacitated()) {
				return currentCreo;
			}
		} else {
			return currentThreat;
		}
	}

	threatMatrix.clear();

	ManagedReference<TangibleObject*> selfStrong = cast<TangibleObject*>(self.get().get());

	for (int i = 0; i < size(); ++i) {
		ThreatMapEntry* entry = &elementAt(i).getValue();
		TangibleObject* tano = elementAt(i).getKey();

		if (tano == nullptr || selfStrong == nullptr) {
			continue;
		}

		// Decay Threat Map
		entry->removeAggro(entry->getAggroMod() / 3);

		if (selfStrong->isCreatureObject()) {
			CreatureObject* selfCreo = selfStrong->asCreatureObject();

			if (selfCreo == nullptr || !tano->isInRange(selfCreo, 128.f) || !tano->isAttackableBy(selfCreo))
				continue;

			if (tano->isCreatureObject()) {
				CreatureObject* creature = tano->asCreatureObject();

				if (creature != nullptr && !creature->isDead() && !creature->isIncapacitated()) {
					threatMatrix.add(creature, entry);
				}
			} else {
				threatMatrix.add(tano, entry);
			}
		} else if (selfStrong->isShipObject()) {
			ShipObject* selfShip = selfStrong->asShipObject();

			if (selfShip == nullptr || !tano->isInRange(selfShip, 512.f) || !tano->isAttackableBy(selfShip))
				continue;

			threatMatrix.add(tano, entry);
		}
	}

	this->currentThreat = threatMatrix.getLargestThreat();

	cooldownTimerMap.updateToCurrentAndAddMili("doEvaluation", ThreatMap::EVALUATIONCOOLDOWN);

	return this->currentThreat.get().get();
}

void ThreatMap::addAggro(TangibleObject* target, int value, uint64 duration) {
	Locker locker(&lockMutex);

	ManagedReference<TangibleObject*> strongSelf = self.get();
	if (strongSelf == nullptr || strongSelf.get() == target)
		return;

	int idx = find(target);

	if (idx == -1) {
		ThreatMapEntry entry;
		entry.addAggro(value);
		put(target, entry);
		registerObserver(target);

	} else {
		ThreatMapEntry* entry = &elementAt(idx).getValue();
		entry->addAggro(value);
	}

	if (duration > 0) {
		Reference<RemoveAggroTask*> removeAggroTask = new RemoveAggroTask(self.get(), target, value);
		removeAggroTask->schedule(duration);
	}
}

void ThreatMap::removeAggro(TangibleObject* target, int value) {
	Locker locker(&lockMutex);

	int idx = find(target);

	if (idx != -1) {
		ThreatMapEntry* entry = &elementAt(idx).getValue();
		entry->removeAggro(value);
	}
}

void ThreatMap::clearAggro(TangibleObject* target) {
	Locker locker(&lockMutex);

	int idx = find(target);

	if (idx != -1) {
		ThreatMapEntry entry;
		entry.clearAggro();
	}
}

void ThreatMap::addHeal(TangibleObject* target, int value) {
	Locker locker(&lockMutex);

	ManagedReference<TangibleObject*> strongSelf = self.get();
	if (strongSelf == nullptr || strongSelf.get() == target)
		return;

	int idx = find(target);

	if (idx == -1) {
		ThreatMapEntry entry;
		entry.addHeal(value);
		entry.addAggro(value*2); // Heals Aggro 2x over damage
		put(target, entry);
		registerObserver(target);

	} else {
		ThreatMapEntry* entry = &elementAt(idx).getValue();
		entry->addHeal(value);
		entry->addAggro(value*2);
	}
}

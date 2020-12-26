/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef DroidAutoHealTask_H_
#define DroidAutoHealTask_H_

#include "server/zone/objects/creature/ai/DroidObject.h"
#include "server/zone/objects/tangible/components/droid/DroidStimpackModuleDataComponent.h"
#include "server/zone/objects/group/GroupObject.h"
#include "templates/params/creature/CreatureAttribute.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace events {

class DroidAutoHealTask : public Task {

	Reference<DroidStimpackModuleDataComponent*> module;
	String droidName;
	int maxUse;
private:
	bool isDamagedEnough(CreatureObject* target, int attribute, int delta){
		const int max = target->getMaxHAM(attribute);
		const int current = target->getHAM(attribute) + target->getWounds(attribute);
		return (max - current) >= delta;
	}
public:
	DroidAutoHealTask(DroidStimpackModuleDataComponent* module, int maxUse, String droidName) : Task() {
		this->module = module;
		this->droidName = droidName;
		this->maxUse = maxUse;
	}

	void run() {
		if (module == nullptr || module->getDroidObject() == nullptr) {
			return;
		}

		DroidObject* droid = module->getDroidObject();
		Locker locker(droid);

		// Check if module is still active
		if (!module->isActive()) {
			droid->removePendingTask("droid_auto_heal");
			return;
		}

		// Check if droid is spawned
		if (droid->getLocalZone() == nullptr) {  // Not outdoors
			ManagedReference<SceneObject*> parent = droid->getParent().get();

			if (parent == nullptr || !parent->isCellObject()) { // Not indoors either
				droid->removePendingTask("droid_auto_heal");
				return;
			}
		}

		// Check droid states
		if (droid->isDead() || droid->isIncapacitated()) {
			droid->removePendingTask("droid_auto_heal");
			return;
		}

		// Droid must have power
		if (!droid->hasPower()) {
			droid->showFlyText("npc_reaction/flytext","low_power", 204, 0, 0);  // "*Low Power*"
			droid->removePendingTask("droid_auto_heal");
			return;
		}

		// Find all damaged players in range
		Vector<CreatureObject*> candidates;
		ManagedReference<GroupObject*> group = droid->getGroup();
		if (group != nullptr) {
			for (int i = 0; i < group->getGroupSize(); i++) {
				Reference<CreatureObject*> member = group->getGroupMember(i);
				if (member != nullptr && member->isPlayerCreature() && !member->isDead() && member->isInRange(droid, 10.0f)) {
					if( isDamagedEnough(member, CreatureAttribute::HEALTH, 200) || isDamagedEnough(member, CreatureAttribute::ACTION, 200) ){
						candidates.add(member);
					}
				}
			}
		}

		if( candidates.size() > 0 ){
			Reference<CreatureObject*> selected = candidates.get(System::random(candidates.size()-1));

			StimPack* stimpack = module->findStimPack(maxUse);
			if (stimpack == nullptr) {
				return;
			}

			Locker locker(droid, selected);
			Locker slocker(stimpack);
			uint32 stimPower = stimpack->calculatePower(droid, selected);

			int healthHealed = 0, actionHealed = 0;
			bool notifyObservers = true;

			if( selected->hasDamage(CreatureAttribute::HEALTH) ){
				if (notifyObservers) {
					healthHealed = selected->healDamage(droid, CreatureAttribute::HEALTH, stimPower);
					notifyObservers = false;
				} else {
					healthHealed = selected->healDamage(droid, CreatureAttribute::ACTION, stimPower, true, false);
				}
			}

			if( selected->hasDamage(CreatureAttribute::ACTION) ){
				if (notifyObservers) {
					actionHealed = selected->healDamage(droid, CreatureAttribute::ACTION, stimPower);
					notifyObservers = false;
				} else {
					actionHealed = selected->healDamage(droid, CreatureAttribute::ACTION, stimPower, true, false);
				}
			}

			if( healthHealed > 0 || actionHealed > 0 ){
				stimpack->decreaseUseCount();
				module->countUses();

            	selected->playEffect("clienteffect/healing_healdamage.cef", "");
				droid->doAnimation("heal_other");

				// send heal message
				StringBuffer msgPlayer, msgTarget, msgBody, msgTail;

				if (healthHealed > 0 && actionHealed > 0) {
					msgBody << healthHealed << " health and " << actionHealed << " action";
				} else if (healthHealed > 0) {
					msgBody << healthHealed << " health";
				} else if (actionHealed > 0) {
					msgBody << actionHealed << " action";
				}

				msgTail << " damage.";
				msgTarget << droidName << " heals you for " << msgBody.toString() << msgTail.toString();

				selected->sendSystemMessage(msgTarget.toString());
				droid->usePower(1);
			}
		}

		// Reschedule task
		reschedule(module->getHealTimeMS());
	}
};

} // events
} // creature
} // objects
} // zone
} // server

using namespace server::zone::objects::creature::events;

#endif /*DroidAutoHealTask_H_*/

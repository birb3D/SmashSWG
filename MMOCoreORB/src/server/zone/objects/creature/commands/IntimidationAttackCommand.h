/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef INTIMIDATIONATTACKCOMMAND_H_
#define INTIMIDATIONATTACKCOMMAND_H_

#include "CombatQueueCommand.h"

class IntimidationAttackCommand : public CombatQueueCommand {
public:

	IntimidationAttackCommand(const String& name, ZoneProcessServer* server) : CombatQueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isAiAgent())
			return GENERALERROR;

		Reference<TangibleObject*> targetObject = server->getZoneServer()->getObject(target).castTo<TangibleObject*>();

		if (targetObject == nullptr || !targetObject->isCreatureObject())
			return INVALIDTARGET;

		int res = doCombatAction(creature, target, arguments);

		if (res == SUCCESS) {

			// Add aggro with intimidate
			CreatureObject* targetCreature = cast<CreatureObject*>(targetObject.get());
			Locker clocker(targetCreature, creature);
			if(targetCreature != nullptr && !targetObject->isPlayerCreature())
				targetCreature->getThreatMap()->addAggro(creature, 6000);

		}

		return res;
	}

};

#endif //INTIMIDATIONATTACKCOMMAND_H_

/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef ADDPOWERTOCOMMAND_H_
#define ADDPOWERTOCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/resource/ResourceManager.h"
#include "server/zone/objects/structure/StructureObject.h"

class AddPowerToCommand : public QueueCommand {
public:

	AddPowerToCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<PlayerManager*> playerManager = server->getPlayerManager();

		uint64 targetid = creature->getTargetID();
		ManagedReference<SceneObject*> obj = playerManager->getInRangeStructureWithAdminRights(creature, targetid);

		if (obj == nullptr || !obj->isStructureObject())
			return INVALIDTARGET;

		StructureObject* structure = cast<StructureObject*>( obj.get());

		if (structure->getBasePowerRate() <= 0) {
			return INVALIDTARGET;
		}

		int amount = 0;

		try {
			UnicodeTokenizer tokenizer(arguments);
			amount = tokenizer.getIntToken();

		} catch (Exception& e) {
			creature->sendSystemMessage("@player_structure:unable_to_parse"); //The system was unable to parse a valid power amount.
			return INVALIDPARAMETERS;
		}

		if (amount < 0) {
			creature->sendSystemMessage("@player_structure:enter_valid_over_zero"); //Please enter a valid power amount greater than 0.
			return INVALIDPARAMETERS;
		}

		ResourceManager* resourceManager = server->getZoneServer()->getResourceManager();
		uint32 totalPower = resourceManager->getAvailablePowerFromPlayer(creature);

		float toAdd = amount - structure->getSurplusPower();
		if (toAdd <= 0) {
			creature->sendSystemMessage("Your structure already has sufficient power");
			return INVALIDPARAMETERS;
		}

		if (totalPower < toAdd) {
			StringIdChatParameter params("@player_structure:not_enough_energy"); //You do not have %DI units of energy in your inventory!
			params.setDI(toAdd);

			creature->sendSystemMessage(params);
			return INVALIDPARAMETERS;
		}

		resourceManager->removePowerFromPlayer(creature, toAdd);

		Locker _lock(structure);
		structure->addPower(toAdd);

		StringIdChatParameter params("@player_structure:deposit_successful"); //You successfully deposit %DI units of energy.
		params.setDI(toAdd);

		creature->sendSystemMessage(params);

		return SUCCESS;
	}

};

#endif //ADDPOWERCOMMAND_H_

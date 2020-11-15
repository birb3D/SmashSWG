/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef PAYMAINTENANCETOCOMMAND_H_
#define PAYMAINTENANCETOCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class PaymaintenanceToCommand : public QueueCommand {
public:

	PaymaintenanceToCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if ((creature->getCashCredits() + creature->getBankCredits()) <= 0) {
			creature->sendSystemMessage("@player_structure:no_money"); //You do not have any money to pay maintenance.
			return GENERALERROR;
		}

		ManagedReference<PlayerManager*> playerManager = server->getPlayerManager();

		uint64 targetid = creature->getTargetID();

		ManagedReference<SceneObject*> obj = playerManager->getInRangeStructureWithAdminRights(creature, targetid);

		if (obj == nullptr || !obj->isStructureObject())
			return INVALIDTARGET;

		StructureObject* structure = cast<StructureObject*>(obj.get());

		Locker clocker(structure, creature);

		ManagedReference<Zone*> zone = structure->getZone();

		if (zone == nullptr)
			return INVALIDPARAMETERS;

		if (structure->isCivicStructure()) {
			creature->sendSystemMessage("@player_structure:civic_structure_alert"); // Civic structure: Maintenance handled by city.
			return INVALIDTARGET;
		}

		if (structure->isGCWBase()) {
			return INVALIDTARGET;
		}

		StructureManager* structureManager = StructureManager::instance();

		UnicodeTokenizer tokenizer(arguments);
		int amount = tokenizer.getIntToken();

		if (amount < 0) {
			creature->sendSystemMessage("Please enter a valid maintenance amount greater than 0"); 
			return INVALIDPARAMETERS;
		}

		float toAdd = amount - structure->getSurplusMaintenance();
		if (toAdd <= 0) {
			creature->sendSystemMessage("Your structure already has sufficient maintenance");
			return INVALIDPARAMETERS;
		}

		if (toAdd > 0) {
			structureManager->payMaintenance(structure, creature, toAdd);
		}

		return SUCCESS;
	}

};

#endif //PAYMAINTENANCETOCOMMAND_H_

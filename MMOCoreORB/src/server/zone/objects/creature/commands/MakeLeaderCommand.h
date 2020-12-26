/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef MAKELEADERCOMMAND_H_
#define MAKELEADERCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/group/GroupObject.h"
#include "server/zone/managers/group/GroupManager.h"
#include "server/zone/objects/creature/CreatureObject.h"


class MakeLeaderCommand : public QueueCommand {
public:

	MakeLeaderCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		GroupManager* groupManager = GroupManager::instance();

		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(target);
		ManagedReference<PlayerManager*> playerManager = server->getPlayerManager();

		CreatureObject* targetObject = nullptr;
		GroupObject* group = creature->getGroup();

		/*

		if (object == nullptr || !object->isPlayerCreature())
			return GENERALERROR;

		CreatureObject* targetObject = cast<CreatureObject*>( object.get());

		*/

		StringTokenizer args(arguments.toString());

		if (object == nullptr || !object->isPlayerCreature()) {
			String firstName;

			if (args.hasMoreTokens()) {
				args.getStringToken(firstName);
				targetObject = playerManager->getPlayer(firstName);
			}
		}

		if (object != nullptr && object->isPlayerCreature())
			targetObject = cast<CreatureObject*>( object.get());

		if (targetObject == nullptr)
			return GENERALERROR;

		if (group == nullptr)
			return GENERALERROR;

		//groupManager->makeLeader(group, creature, targetObject);

		if (!targetObject->getPlayerObject()->isIgnoring(creature->getFirstName().toLowerCase()))
			groupManager->makeLeader(group, creature, targetObject);


		return SUCCESS;
	}

};

#endif //MAKELEADERCOMMAND_H_


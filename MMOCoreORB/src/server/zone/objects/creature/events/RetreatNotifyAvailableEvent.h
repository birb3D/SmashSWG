/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef RETREATNOTIFYAVAILABLEEVENT_H_
#define RETREATNOTIFYAVAILABLEEVENT_H_

#include "server/zone/objects/creature/CreatureObject.h"

class RetreatNotifyAvailableEvent : public Task {
	ManagedWeakReference<CreatureObject*> creo;

public:
	RetreatNotifyAvailableEvent(CreatureObject* cr) : Task() {
		creo = cr;
	}

	void run() {
		ManagedReference<CreatureObject*> creature = creo.get();

		if (creature == nullptr)
			return;

		Locker locker(creature);

		creature->removePendingTask("retreat_notify");
		creature->sendSystemMessage("You are no longer strained by trying to manage your squad."); //"You are no longer tired.";
	}

};

#endif /*RETREATNOTIFYAVAILABLEEVENT_H_*/

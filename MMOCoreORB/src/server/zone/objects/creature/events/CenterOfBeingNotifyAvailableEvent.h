/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CENTEROFBEINGNOTIFYAVAILABLEEVENT_H_
#define CENTEROFBEINGNOTIFYAVAILABLEEVENT_H_

#include "server/zone/objects/creature/CreatureObject.h"

class CenterOfBeingNotifyAvailableEvent : public Task {
	ManagedWeakReference<CreatureObject*> creo;

public:
	CenterOfBeingNotifyAvailableEvent(CreatureObject* cr) : Task() {
		creo = cr;
	}

	void run() {
		ManagedReference<CreatureObject*> creature = creo.get();

		if (creature == nullptr)
			return;

		Locker locker(creature);

		creature->removePendingTask("center_of_being_notify");
		creature->sendSystemMessage("You find yourself calm and able to find your center again"); //"You are no longer tired.";
	}

};

#endif /*CENTEROFBEINGNOTIFYAVAILABLEEVENT_H_*/

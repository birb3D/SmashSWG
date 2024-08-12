/*
 * DiscardDroneStimpacksSuiCallback.h
 *
 */

#ifndef DISCARDDRONESTIMPACKSSUICALLBACK_H_
#define DISCARDDRONESTIMPACKSSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/tangible/components/droid/DroidStimpackModuleDataComponent.h"
#include "server/zone/objects/creature/ai/DroidObject.h"

#include <iostream>

class DiscardDroneStimpacksSuiCallback : public SuiCallback {
public:
	DiscardDroneStimpacksSuiCallback(ZoneServer* server) : SuiCallback(server) {}

	void run(CreatureObject* player, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		PlayerManager* playerManager = player->getZoneServer()->getPlayerManager();
		if( !suiBox->isMessageBox() || playerManager == nullptr ){
			std::cout << "Box Manager" << std::endl;
			return;
		}

		if( cancelPressed ){
			std::cout << "Cancel" << std::endl;
			return;
		}

		ManagedReference<SceneObject*> object = suiBox->getUsingObject().get();
		if (object == nullptr) {
			std::cout << "Object" << std::endl;
			return;
		}

		DroidObject* droid = cast<DroidObject*>(object.get());
		if (droid == nullptr){
			std::cout << "Droid" << std::endl;
			return;
		}

		auto module = droid->getModule("stimpack_module").castTo<DroidStimpackModuleDataComponent*>();
		if(module == nullptr) {
			std::cout << "Module" << std::endl;
			return;
		}

		Locker locker(droid);
		module->discardStimpacks();
	}
};

#endif /* DISCARDDRONESTIMPACKSSUICALLBACK_H_ */

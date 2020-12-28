/*
 * GamblingCrapsSuiCallback.h
 *
 *  Created on: 12/27, 2020
 *      Author: Smashley
 */

#ifndef GAMBLINGCRAPSSUICALLBACK_H_
#define GAMBLINGCRAPSSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/managers/minigames/GamblingManager.h"

class GamblingCrapsSuiCallback : public SuiCallback {
public:
	GamblingCrapsSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}

	void run(CreatureObject* player, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);
		bool foldPressed  = Bool::valueOf(args->get(0).toString());

		if (!suiBox->isListBox() || player == nullptr)
			return;

		GamblingManager* manager = player->getZoneProcessServer()->getGamblingManager();

		Locker locker(manager);

		if (cancelPressed)
			manager->leaveTerminal(player, 2);
		else if (foldPressed) {
			manager->pullCrapsBets(player);
			manager->refreshCrapsMenu(player);
		}
		else
			manager->refreshCrapsMenu(player);
	}
};

#endif /* GAMBLINGCRAPSSUICALLBACK_H_ */

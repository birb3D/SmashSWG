/*
 * GamblingManagerImplementation.cpp
 *
 *  Created on: Apr 11, 2010
 *      Author: swgemu
 */

#include "server/zone/managers/minigames/GamblingManager.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/tangible/terminal/gambling/GamblingTerminal.h"
#include "server/zone/ZoneServer.h"
#include "server/chat/StringIdChatParameter.h"
#include "system/util/Vector.h"
#include "system/util/VectorMap.h"
#include "server/zone/managers/minigames/events/GamblingEvent.h"
#include "server/zone/objects/player/sui/slotmachinebox/SuiSlotMachineBox.h"
#include "server/zone/objects/player/sui/callbacks/GamblingSlotSuiCallback.h"
#include "server/zone/objects/player/sui/callbacks/GamblingRouletteSuiCallback.h"
#include "server/zone/objects/player/sui/callbacks/GamblingCrapsSuiCallback.h"
#include "server/zone/objects/player/sui/callbacks/GamblingSlotPayoutSuiCallback.h"
#include "server/zone/managers/minigames/GamblingBet.h"
#include "server/zone/objects/transaction/TransactionLog.h"

void GamblingManagerImplementation::registerPlayer(GamblingTerminal* terminal, CreatureObject* player) {
	if (terminal == nullptr || player == nullptr)
		return;

	Locker _locker(_this.getReferenceUnsafeStaticCast());
	switch (terminal->getMachineType()) {
		case GamblingTerminal::SLOTMACHINE: {
			slotGames.put(player, terminal);
			break;
		}
		case GamblingTerminal::ROULETTEMACHINE: {
			rouletteGames.put(player, terminal);
			break;
		}
		case GamblingTerminal::CRAPS: {
			crapsGames.put(player, terminal);
			break;
		}
	}
}

uint32 GamblingManagerImplementation::createWindow(GamblingTerminal* terminal, CreatureObject* player) {
	if (terminal == nullptr || player == nullptr)
		return 0;

	uint32 boxID=0;

	switch (terminal->getMachineType()) {
		case GamblingTerminal::SLOTMACHINE: {

			boxID = createPayoutWindow(player);
			boxID = createSlotWindow(player, boxID);

			break;
		}
		case GamblingTerminal::ROULETTEMACHINE: {

			boxID = createRouletteWindow(player);

			break;
		}
		case GamblingTerminal::CRAPS: {

			boxID = createCrapsWindow(player);

			break;
		}
	}

	return boxID;
}

uint32 GamblingManagerImplementation::createSlotWindow(CreatureObject* player, uint32 payoutBoxID) {
	if (player == nullptr)
		return 0;

	ManagedReference<GamblingTerminal*> terminal = slotGames.get(player);
	ZoneServer* server = player->getZoneServer();

	if (terminal == nullptr)
		return 0;

	String prompt = "Press the button corresponding to the desired action.";

	int amount = 0;

	bool quit = true;

	if (!terminal->getBets()->isEmpty()) {
		amount = terminal->getBets()->get(0)->getAmount();
		quit = false;
	}

	// create new window
	ManagedReference<SuiSlotMachineBox*> box = new SuiSlotMachineBox(player, SuiWindowType::GAMBLING_SLOT, payoutBoxID, 3);

	box->setUsingObject(terminal);

	box->setPromptTitle("@gambling/game_n:slot_standard");
	box->setPromptText(prompt);

	box->addMenuItem("Current Bet: " + String::valueOf(amount), 0);
	box->addMenuItem("Max Bet: " + String::valueOf(terminal->getMaxBet()), 1);
	box->addMenuItem("Cash Balance: " + String::valueOf(player->getCashCredits()), 2);
	box->addMenuItem("Bank Balance: " + String::valueOf(player->getBankCredits()), 3);
	box->addMenuItem("Total Money: " + String::valueOf(player->getCashCredits() + player->getBankCredits()), 4);

	if (quit)
		box->setCancelButton(true, "@ui:quit");
	else
		box->setCancelButton(true, "@ui:spin");

	//box->setOtherButton(true,"Bet " + String::valueOf(terminal->getMinBet()));
	//box->setOtherButton(true, "@ui:bet_one");
	box->setOtherButton(true, "@gambling/default_interface:opt_bet");
	box->setOkButton(true, "@ui:bet_max");

	box->setForceCloseDistance(32.f);
	box->setCallback(new GamblingSlotSuiCallback(server));


	player->getPlayerObject()->addSuiBox(box);

	player->sendMessage(box->generateMessage());

	return box->getBoxID();
}

uint32 GamblingManagerImplementation::createRouletteWindow(CreatureObject* player) {
	if (player == nullptr)
		return 0;

	int totalBet = 0;

	String prompt = "The following is a summary of your current bets...\n\nUse /bet <amount> <1-36,0,00,red,black,odd,even,high,low> to wager.\nExample: '/bet 5 black' to wager 5 credits on black\n\nCash : "
			+ String::valueOf(player->getCashCredits())
			+ "\nBank : "
			+ String::valueOf(player->getBankCredits())
			+ "\nTotal: "
			+ String::valueOf(player->getCashCredits() + player->getBankCredits())
			+ "\n\nNOTE: If you leave the table after placing a bet, all of your outstanding bets will be forfeit.";

	// create new window
	ManagedReference<SuiListBox*> box = new SuiListBox(player, SuiWindowType::GAMBLING_ROULETTE, 2);
	box->setPromptTitle("@gambling/game_n:roulette");
	box->setPromptText(prompt);

	ManagedReference<GamblingTerminal*> terminal = rouletteGames.get(player);

	box->setUsingObject(terminal);

	if (terminal->getBets()->size() != 0) {
		for (int i=0; i < terminal->getBets()->size(); ++i) {
			if (terminal->getBets()->get(i)->getPlayer() == player) {
				totalBet += terminal->getBets()->get(i)->getAmount();
				String target = terminal->getBets()->get(i)->getTarget();
				target[0] = toupper(target[0]);
				box->addMenuItem(target + ": " + String::valueOf(terminal->getBets()->get(i)->getAmount()), i);
			}
		}
	}

	if (totalBet == 0) {
		box->addMenuItem("Total Bet : 0", 0);
	} else {
		box->addMenuItem(" ", -2);
		box->addMenuItem("Total Bet : "+String::valueOf(totalBet), -3);
	}
	box->setCancelButton(true, "@ui:leave_game");
	box->setOtherButton(false, "");
	box->setOkButton(true, "@ui:refresh");

	box->setForceCloseDistance(32.f);

	ZoneServer* server = player->getZoneServer();

	box->setCallback(new GamblingRouletteSuiCallback(server));

	player->getPlayerObject()->addSuiBox(box);

	player->sendMessage(box->generateMessage());

	return box->getBoxID();
}

uint32 GamblingManagerImplementation::createCrapsWindow(CreatureObject* player) {
	if (player == nullptr)
		return 0;

	int totalBet = 0;



	// create new window
	ManagedReference<SuiListBox*> box = new SuiListBox(player, SuiWindowType::GAMBLING_CRAPS, 3);
	box->setPromptTitle("CRAPS");

	ManagedReference<GamblingTerminal*> terminal = crapsGames.get(player);

	String prompt = "\\#ffffffPASS LINE: " + (terminal->getButton() < 4 ? "\\#00ff00OPEN" : ("\\#ff0000CLOSED\n\\#00ff00BUTTON: " + String::valueOf(terminal->getButton()))) + "\n"
				+ "\n"
				+ "\\#ffffffUse /bet <amount> <option> to wager.\nExample: '/bet 5 pass' to wager 5 credits on the pass line\n\n"
				+ "\\#fff175Pass Bets: \\#ffffffpass, nopass\n"
				+ "\\#5bff71ANY TIME BETS:\n"
				+ "\\#fff175One Roll Bets: \\#ffffff2, 3, 7, 11, 12, craps, field, hilo, horn\n"
				+ "\\#fff175Lay Bets: \\#fffffflay4, lay5, lay6, lay8, lay9, lay10\n"
				+ "\\#5bff71BUTTON ONLY BETS:\n"
				+ "\\#fff175Place Bets: \\#ffffff4, 5, 6, 8, 9, 10, odds\n"
				+ "\\#fff175Hard Ways: \\#ffffffhard4, hard6, hard8, hard10\n"
				+ "\nCash : "
				+ String::valueOf(player->getCashCredits())
				+ "\n\nNOTE: Pass/No Pass bets cannot be pulled after the button is established. If you leave the table you will pull back whatever bets you can.";

	box->setPromptText(prompt);

	box->setUsingObject(terminal);


	if (terminal->getBets()->size() != 0) {
		for (int i=0; i < terminal->getBets()->size(); ++i) {
			if (terminal->getBets()->get(i)->getPlayer() == player) {
				totalBet += terminal->getBets()->get(i)->getAmount();
				String target = terminal->getBets()->get(i)->getTarget();
				target[0] = toupper(target[0]);
				box->addMenuItem(target + ": " + String::valueOf(terminal->getBets()->get(i)->getAmount()), i);
			}
		}
	}



	if (totalBet == 0) {
		box->addMenuItem("Total Bet : 0", 0);
	} else {
		box->addMenuItem(" ", -2);
		box->addMenuItem("Total Bet : "+String::valueOf(totalBet), -3);
	}
	box->setCancelButton(true, "@ui:leave_game");
	box->setOtherButton(true, "@cmd_n:pull");
	box->setOkButton(true, "@ui:refresh");

	box->setForceCloseDistance(32.f);

	ZoneServer* server = player->getZoneServer();

	box->setCallback(new GamblingCrapsSuiCallback(server));

	player->getPlayerObject()->addSuiBox(box);

	player->sendMessage(box->generateMessage());

	return box->getBoxID();
}

uint32 GamblingManagerImplementation::createPayoutWindow(CreatureObject* player) {
	if (player == nullptr)
		return 0;

	String prompt = "The following is the payout schedule for this slot machine.\n \nLegend:\nXXX: denotes any 3 of the same number\n*X|Y|Z: denotes any combination of the 3 numbers";

	// create new window
	ManagedReference<SuiListBox*> box = new SuiListBox(player, SuiWindowType::GAMBLING_SLOT_PAYOUT, 1);
	box->setPromptTitle("PAYOUT SCHEDULE");
	box->setPromptText(prompt);
	box->addMenuItem("*1|2|3 -> 2x", 0);
	box->addMenuItem("000 -> 10x", 1);
	box->addMenuItem("111 -> 20x", 2);
	box->addMenuItem("222 -> 50x", 3);
	box->addMenuItem("333 -> 100x", 3);
	box->addMenuItem("444 -> 250x", 3);
	box->addMenuItem("555 -> 500x", 3);
	box->addMenuItem("666 -> 1000x", 3);
	box->addMenuItem("777 -> 1500x", 3);
	box->setCancelButton(false, "");
	box->setOtherButton(false, "");
	box->setOkButton(true, "@ui:ok");

	ZoneServer* server = player->getZoneServer();

	box->setCallback(new GamblingSlotPayoutSuiCallback(server));

	player->getPlayerObject()->addSuiBox(box);
	player->sendMessage(box->generateMessage());

	return box->getBoxID();
}

void GamblingManagerImplementation::refreshRouletteMenu(CreatureObject* player) {

	if (player != nullptr) {

		ManagedReference<GamblingTerminal*> terminal = rouletteGames.get(player);
		terminal->closeMenu(player, false);

		terminal->getPlayersWindows()->drop(player);
		terminal->getPlayersWindows()->put(player, createRouletteWindow(player));
	}
}

void GamblingManagerImplementation::refreshCrapsMenu(CreatureObject* player) {

	if (player != nullptr) {

		ManagedReference<GamblingTerminal*> terminal = crapsGames.get(player);
		terminal->closeMenu(player, false);

		terminal->getPlayersWindows()->drop(player);
		terminal->getPlayersWindows()->put(player, createCrapsWindow(player));
	}
}

void GamblingManagerImplementation::pullCrapsBets(CreatureObject* player) {
	info("(Craps) Removing bets for pull");

	if( player == nullptr ) return;

	ManagedReference<GamblingTerminal*> terminal = crapsGames.get(player);
	if( terminal == nullptr || terminal->getState() >= 3 ) {
		return;
	}

	int tempReward = 0;
	Vector<Reference<GamblingBet*>> remainingBets;

	for (int i=0; i < terminal->getBets()->size(); ++i) {
		GamblingBet *bet = terminal->getBets()->get(i);

		if(player != bet->getPlayer()){
			remainingBets.add(bet);
			continue;
		}

		if(terminal->getButton() >= 4) {
			if(bet->getTarget() == "pass" || bet->getTarget() == "nopass"){
				remainingBets.add(bet);
				continue;
			}
		}

		tempReward += bet->getAmount();
	}

	Locker locker(terminal);
	terminal->setBets(&remainingBets);

	if( tempReward == 0 ) return;

	StringIdChatParameter textPlayer("gambling/default_interface","prose_payout");
	textPlayer.setDI(tempReward);
	player->sendSystemMessage(textPlayer);

	TransactionLog trx(TrxCode::GAMBLINGROULETTE, player, tempReward, true);
	player->addCashCredits(tempReward, true);
}

void GamblingManagerImplementation::refreshSlotMenu(CreatureObject* player, GamblingTerminal* terminal) {
	if (player == nullptr || terminal == nullptr)
		return;

	terminal->closeMenu(player, false);

	terminal->getPlayersWindows()->drop(player);
	terminal->getPlayersWindows()->put(player, createSlotWindow(player, 0));
}

void GamblingManagerImplementation::handleSlot(CreatureObject* player, bool cancel, bool other) {
	if (player == nullptr)
		return;

	ManagedReference<GamblingTerminal*> terminal = slotGames.get(player);

	bool hasBets = !terminal->getBets()->isEmpty();

	if (cancel) {
		if (hasBets)
			startGame(player, 1);
		else
			leaveTerminal(player, 1);
	} else if (other) {
		bet(terminal, player, terminal->getMinBet(), 0);
	} else {
		if (hasBets)
			bet(terminal, player, terminal->getMaxBet() - terminal->getBets()->get(0)->getAmount(), 0);
		else
			bet(terminal, player, terminal->getMaxBet(), 0);
	}
}

void GamblingManagerImplementation::bet(CreatureObject* player, int amount, int target, int machineType) {
	if (player == nullptr)
		return;

	if (machineType == 0) {
		bet(rouletteGames.get(player), player, amount, target);
		refreshRouletteMenu(player);

	} else if (machineType == 1) {
		bet(slotGames.get(player), player, amount, target);
	}
	else if (machineType == 2) {
		bet(crapsGames.get(player), player, amount, target);
		refreshCrapsMenu(player);

	}
}

void GamblingManagerImplementation::bet(GamblingTerminal* terminal, CreatureObject* player, int amount, int target) {
	if (player == nullptr || terminal == nullptr)
		return;

	switch (terminal->getMachineType()) {
		case GamblingTerminal::SLOTMACHINE: {
			if (amount > terminal->getMaxBet()) {

				StringIdChatParameter body("gambling/default_interface","bet_above_max");
				body.setDI(terminal->getMaxBet());

				player->sendSystemMessage(body);

			} else if (player->getCashCredits() < amount) {

				player->sendSystemMessage("@gambling/default_interface:player_broke");

			} else if (!player->isInRange(terminal, 25.0)) {

				player->sendSystemMessage("@gambling/default_interface:bet_failed_distance");

			} else if (amount < terminal->getMinBet()) {

				StringIdChatParameter body("gambling/default_interface","bet_below_min");
				body.setDI(terminal->getMinBet());

				player->sendSystemMessage(body);

			} else {
				Locker _locker(terminal);

				{
					TransactionLog trx(player, TrxCode::GAMBLINGSLOTSTANDARD, amount, true);
					player->subtractCashCredits(amount);
				}

				StringIdChatParameter textPlayer("base_player","prose_pay_success");
				textPlayer.setDI(amount);

				String terminalName;
				terminal->getObjectName()->getFullPath(terminalName);
				textPlayer.setTT(terminalName);

				player->sendSystemMessage(textPlayer);

				if (!terminal->getBets()->isEmpty()) {
					amount += terminal->getBets()->get(0)->getAmount();
					terminal->getBets()->removeAll();
				}

				terminal->getBets()->add(new GamblingBet(player, amount));

				if (amount >= terminal->getMaxBet())
					startGame(player, 1);
				else
					refreshSlotMenu(player, terminal);
			}
			break;
		}
		case GamblingTerminal::ROULETTEMACHINE: {
			if (amount > terminal->getMaxBet()) {

				StringIdChatParameter body("gambling/default_interface","bet_above_max");
				body.setDI(terminal->getMaxBet());

				player->sendSystemMessage(body);

			} else if (player->getCashCredits() < amount) {

				player->sendSystemMessage("@gambling/default_interface:player_broke");

			} else if (!player->isInRange(terminal, 25.0)) {

				player->sendSystemMessage("@gambling/default_interface:bet_failed_distance");

			} else if (amount < terminal->getMinBet()) {

				StringIdChatParameter body("gambling/default_interface","bet_below_min");
				body.setDI(terminal->getMinBet());

				player->sendSystemMessage(body);

			} else {
				Locker _locker(terminal);
				{
					TransactionLog trx(player, TrxCode::GAMBLINGROULETTE, amount, true);
					player->subtractCashCredits(amount);
				}
				terminal->getBets()->add(new GamblingBet(player, amount, roulette.get(target)));
				StringIdChatParameter textPlayer("gambling/default_interface","prose_bet_placed");
				textPlayer.setDI(amount);
				player->sendSystemMessage(textPlayer);
			}
			break;
		}
		case GamblingTerminal::CRAPS: {
			if (amount > terminal->getMaxBet()) {

				StringIdChatParameter body("gambling/default_interface","bet_above_max");
				body.setDI(terminal->getMaxBet());

				player->sendSystemMessage(body);

			} else if (player->getCashCredits() < amount) {

				player->sendSystemMessage("@gambling/default_interface:player_broke");

			} else if (!player->isInRange(terminal, 25.0)) {

				player->sendSystemMessage("@gambling/default_interface:bet_failed_distance");

			} else if (amount < terminal->getMinBet()) {

				StringIdChatParameter body("event_/default_interface","bet_below_min");
				body.setDI(terminal->getMinBet());

				player->sendSystemMessage(body);

			} else if (terminal->getButton() < 4 && target >= 17 ) {

				player->sendSystemMessage("That bet can only be placed after the button has been established.");

			} else if (terminal->getButton() >= 4 && target < 2 ) {

				player->sendSystemMessage("You can only bet on the pass line when there is no button.");

			} else if (terminal->getState() < 3 && ((terminal->getButton() >= 4 && target >= 2) || (terminal->getButton() < 4 && target < 17))){
				Locker _locker(terminal);

				GamblingBet *existing = nullptr;
				for (int i=0; i < terminal->getBets()->size(); ++i) {
					GamblingBet *bet = terminal->getBets()->get(i);

					// Ignore other player
					if(player != bet->getPlayer()){
						continue;
					}

					if(bet->getTarget() != craps.get(target)){
						continue;
					}

					existing = bet;
				}

				if( existing == nullptr ){
					{
						TransactionLog trx(player, TrxCode::GAMBLINGCRAPS, amount, true);
						player->subtractCashCredits(amount);
					}
					terminal->getBets()->add(new GamblingBet(player, amount, craps.get(target)));

					StringIdChatParameter textPlayer("gambling/default_interface","prose_bet_placed");
					textPlayer.setDI(amount);
					player->sendSystemMessage(textPlayer);
				}else{
					if( existing->getAmount() > terminal->getMaxBet()) {
						StringIdChatParameter body("gambling/default_interface","bet_above_max");
						body.setDI(terminal->getMaxBet());
						player->sendSystemMessage(body);
					}else{
						{
							TransactionLog trx(player, TrxCode::GAMBLINGCRAPS, amount, true);
							player->subtractCashCredits(amount);
						}
						existing->setAmount(existing->getAmount() + amount);
						
						StringIdChatParameter textPlayer("gambling/default_interface","prose_bet_placed");
						textPlayer.setDI(amount);
						player->sendSystemMessage(textPlayer);
					}
				}
			}
			else if(terminal->getState() >= 3){
				player->sendSystemMessage("You can't bet while the dice are rolling or during payouts.");
			}
			else {
				player->sendSystemMessage("@gambling/saarlac_wheel:invalid_bet");
			}

			break;
		}
	}
}

void GamblingManagerImplementation::startGame(CreatureObject* player, int machineType) {

	if (player != nullptr) {
		switch (machineType) {
			case GamblingTerminal::SLOTMACHINE: {
				startGame(slotGames.get(player));
				break;
			}
			case GamblingTerminal::ROULETTEMACHINE: {
				startGame(rouletteGames.get(player));
				break;
			}
			case GamblingTerminal::CRAPS: {
				startGame(crapsGames.get(player));
				break;
			}
		}
	}
}

void GamblingManagerImplementation::startGame(GamblingTerminal* terminal) {

	if (terminal != nullptr) {

		switch (terminal->getMachineType()) {
			case GamblingTerminal::SLOTMACHINE: {

				Locker _locker(terminal);

				terminal->setState(GamblingTerminal::GAMESTARTED);

				//bet(terminal, terminal->getPlayersWindows()->elementAt(0).getKey(), 3, 0);

				terminal->statusUpdate(terminal->getState());

				createEvent(terminal, slotTimer.get(terminal->getState() - 2) * 1000);

				break;
			}
			case GamblingTerminal::ROULETTEMACHINE: {

				terminal->statusUpdate(terminal->getState());

				createEvent(terminal, rouletteTimer.get(terminal->getState() - 1) * 1000);

				break;
			}
			case GamblingTerminal::CRAPS: {

				terminal->statusUpdate(terminal->getState());

				createEvent(terminal, crapsTimer.get(terminal->getState() - 1) * 1000);

				break;
			}
		}
	}
}

void GamblingManagerImplementation::createEvent(GamblingTerminal* terminal, int time) {
	if ((terminal != nullptr) && (time > 0) && (time < 60000)) {

		terminal->setEvent(new GamblingEvent(terminal, terminal->getGameCount()));
		terminal->getEvent()->schedule(time);
	}
}

void GamblingManagerImplementation::continueGame(GamblingTerminal* terminal) {

	if (terminal != nullptr) {
		Locker _locker(terminal);

		if (terminal->getPlayersWindows()->size() != 0) {

			switch (terminal->getMachineType()) {
				case GamblingTerminal::SLOTMACHINE: {

					if (terminal->getState() == GamblingTerminal::SLOTGAMEENDED) {
						//createNextRound
						terminal->joinTerminal(terminal->getPlayersWindows()->elementAt(0).getKey());

					} else {

						if (terminal->getState() == GamblingTerminal::END) {

							stopGame(terminal, false);

						} else {

							terminal->setState(terminal->getState() + 1);

							terminal->statusUpdate(terminal->getState());

							createEvent(terminal, slotTimer.get(terminal->getState() - 2) * 1000);
						}
					}

					break;
				}
				case GamblingTerminal::ROULETTEMACHINE: {

					if (terminal->getState() == GamblingTerminal::WHEELPAYOUT) {

						stopGame(terminal, false);

					} else {

						terminal->setState(terminal->getState() + 1);

						terminal->statusUpdate(terminal->getState());

						createEvent(terminal, rouletteTimer.get(terminal->getState() - 1) * 1000);
					}

					break;
				}
				case GamblingTerminal::CRAPS: {

					if(terminal->getState() == 5) {
						int total = terminal->getFirst() + terminal->getSecond();


						if(terminal->getButton() >= 4 && total == 7)
							terminal->setState(7); // end game
						else
							terminal->setState(6); // roll again

						createEvent(terminal, 2000);
					}
					else if (terminal->getState() == 6) {
						// pay logic and continue
						calculateOutcome(terminal);
						terminal->setState(1);
						terminal->statusUpdate(1);
						createEvent(terminal, crapsTimer.get(0) * 1000);

					}
					else if (terminal->getState() == 7) {

						stopGame(terminal, false);

					} else {

						terminal->setState(terminal->getState() + 1);

						terminal->statusUpdate(terminal->getState());

						createEvent(terminal, crapsTimer.get(terminal->getState() - 1) * 1000);
					}

					break;
				}
			}
		}
	}
}

void GamblingManagerImplementation::stopGame(GamblingTerminal* terminal, bool cancel) {
	if (terminal != nullptr) {
		Locker _locker(terminal);

		switch (terminal->getMachineType()) {
			case GamblingTerminal::SLOTMACHINE: {

				if (!cancel) {
					calculateOutcome(terminal);

					terminal->closeAllMenus();

					terminal->setState(GamblingTerminal::SLOTGAMEENDED);

					terminal->statusUpdate(terminal->getState());

					terminal->getBets()->removeAll();

					createEvent(terminal, slotTimer.get(terminal->getState() - 2) * 1000);
				} else {
					terminal->closeAllMenus();

					if ((terminal->getEvent() != nullptr) && (terminal->getState() >= GamblingTerminal::GAMESTARTED)) {
						terminal->getEvent()->cancel();
					}

					terminal->reset();
				}

				break;
			}
			case GamblingTerminal::ROULETTEMACHINE: {

				if (!cancel) {

					calculateOutcome(terminal);

					terminal->closeAllMenus();

					terminal->reset();
				} else {

					terminal->closeAllMenus();

					if (terminal->getEvent() != nullptr) {
						terminal->getEvent()->cancel();
					}

					terminal->reset();
				}
				break;
			}
			case GamblingTerminal::CRAPS: {

				if (!cancel) {

					calculateOutcome(terminal);

					terminal->closeAllMenus();

					terminal->reset();
				} else {

					terminal->closeAllMenus();

					if (terminal->getEvent() != nullptr) {
						terminal->getEvent()->cancel();
					}

					terminal->reset();
				}
				break;
			}
		}

	}
}

void GamblingManagerImplementation::calculateOutcome(GamblingTerminal* terminal) {


	if (terminal != nullptr) {

		Locker locker(terminal);

		switch (terminal->getMachineType()) {

			case GamblingTerminal::SLOTMACHINE: {

				GamblingBet* bet = terminal->getBets()->get(0);

				ManagedReference<CreatureObject*> player = terminal->getPlayersWindows()->elementAt(0).getKey();

				if ((bet != nullptr) && (player != nullptr)) {

					if (terminal->getFirst() == terminal->getSecond() && terminal->getSecond() == terminal->getThird()) {

						Locker _locker(player);

						int win = bet->getAmount() * slot.get(terminal->getFirst());

						StringIdChatParameter textPlayer("gambling/default_interface","winner_to_winner");
						textPlayer.setDI(win);
						player->sendSystemMessage(textPlayer);

						{
							TransactionLog trx(TrxCode::GAMBLINGSLOTSTANDARD, player, win, true);
							player->addCashCredits(win, true);
						}

					} else if ((0 < terminal->getFirst() && terminal->getFirst() < 4) && (0 < terminal->getSecond() && terminal->getSecond() < 4) && (0 < terminal->getThird() && terminal->getThird() < 4)) {

						Locker _locker(player);

						int win = bet->getAmount() * 2;

						StringIdChatParameter textPlayer("gambling/default_interface","winner_to_winner");
						textPlayer.setDI(win);
						player->sendSystemMessage(textPlayer);

						{
							TransactionLog trx(TrxCode::GAMBLINGSLOTSTANDARD, player, win, true);
							player->addCashCredits(win, true);
						}
					} else {

						player->sendSystemMessage("Sorry, you did not win this round. Please try again.");

					}

				}

				break;
			}
			case GamblingTerminal::ROULETTEMACHINE: {

				VectorMap<ManagedReference<CreatureObject*>, int>* winnings = terminal->getWinnings();

				auto bets = terminal->getBets();

				int tempReward;
				String tempTarget;

				for (int i=0; i < bets->size(); ++i) {
					tempTarget = bets->get(i)->getTarget();

					if ((tempTarget == "odd" && isOdd(terminal->getFirst())) ||
						(tempTarget == "even" && isEven(terminal->getFirst())) ||
						(tempTarget == "high" && isHigh(terminal->getFirst())) ||
						(tempTarget == "low" && isLow(terminal->getFirst())) ||
						(tempTarget == "red" && isRed(terminal->getFirst())) ||
						(tempTarget == "black" && isBlack(terminal->getFirst()))
					) {

						tempReward = (bets->get(i)->getAmount() * 2);

						if (winnings->contains(bets->get(i)->getPlayer())) {

							tempReward += winnings->get(bets->get(i)->getPlayer());

							winnings->drop(bets->get(i)->getPlayer());

						}

						winnings->put(bets->get(i)->getPlayer(), tempReward);

					} else {
						// single number: 0,00,1-36

						if (tempTarget == roulette.get(terminal->getFirst())) {

							tempReward = ((bets->get(i)->getAmount() * 36));

							if (winnings->contains(bets->get(i)->getPlayer())) {

								tempReward += winnings->get(bets->get(i)->getPlayer());

								winnings->drop(bets->get(i)->getPlayer());
							}

							winnings->put(bets->get(i)->getPlayer(), tempReward);
						}
					}

				}

				for (int i = 0; i < winnings->size(); ++i) { // send money and messages to players

					if (winnings->get(i) == 0) {

						winnings->elementAt(i).getKey()->sendSystemMessage("You don't win anything");

					} else {

						CreatureObject* player = winnings->elementAt(i).getKey();

						if (player != nullptr) {

							Locker _locker(player);

							// Send message to others
							StringIdChatParameter textOther("gambling/default_interface","winner_to_other");
							textOther.setDI(winnings->get(i));
							textOther.setTO(player->getFirstName());
							textOther.setTO(player->getObjectID());
							terminal->notifyOthers(player, &textOther);

							StringIdChatParameter textPlayer("gambling/default_interface","winner_to_winner");
							textPlayer.setDI(winnings->get(i));
							player->sendSystemMessage(textPlayer);

							{
								TransactionLog trx(TrxCode::GAMBLINGROULETTE, player, winnings->get(i), true);
								player->addCashCredits(winnings->get(i), true);
							}
						}
					}
				}

				break;
			}
			case GamblingTerminal::CRAPS: {
				VectorMap<ManagedReference<CreatureObject*>, int>* winnings = terminal->getWinnings();
				winnings->removeAll();

				int total = terminal->getFirst() + terminal->getSecond();
				info("(Craps) Removing bets for payouts");

				// Button Not Established payouts
				Vector<Reference<GamblingBet*>> remainingBets;
				for (int i=0; i < terminal->getBets()->size(); ++i) {
					GamblingBet *bet = terminal->getBets()->get(i);
					const String tempTarget = bet->getTarget();

					// Initialize winnings for all players
					if (!winnings->contains(bet->getPlayer())) {
						winnings->put(bet->getPlayer(), 0);
					}

					int tempReward = 0;
					bool remove = false;

					if(terminal->getButton() < 4) { // No Button (pass/nopass)

						if(total == 11 || total == 7) {
							if(tempTarget == "pass")
								tempReward = bet->getAmount();
							else if(tempTarget == "nopass")
								remove = true;
						}
						else if(total == 2 || total == 3) {
							if(tempTarget == "nopass")
								tempReward = bet->getAmount();
							else if(tempTarget == "pass")
								remove = true;
						}
					}
					else { // Button Bets

						if(terminal->getButton() == total) { // Button hit
							// Pass line
							if(tempTarget == "pass") {
								tempReward = bet->getAmount();
							}
							else if(tempTarget == "odds") {
								tempReward = bet->getAmount() * 3; // 4 and 10
								if(total == 5 || total == 9) tempReward = bet->getAmount() * 5 / 2;
								else if(total == 6 || total == 8) tempReward = bet->getAmount() * 9 / 5;
								remove = true;
							}
							else if(tempTarget == "nopass")
								remove = true;
						}
						else if(total == 7) {
							// No Pass line
							if(tempTarget == "nopass") {
								tempReward = bet->getAmount() * 2;
							}
							else if(tempTarget == "pass" || tempTarget == "hard4" || tempTarget == "hard6" || tempTarget == "hard8" || tempTarget == "hard10")
								remove = true;
						}


						if(total == 4) {
							if(tempTarget == "4")
								tempReward = bet->getAmount() * 9 / 5;
							else if(tempTarget == "hard4") {
								if(terminal->getFirst() == terminal->getSecond())
									tempReward = bet->getAmount() * 8;
								else
									remove = true;
							}
						}
						else if(total == 5) {
							if(tempTarget == "5")
								tempReward = bet->getAmount() * 7 / 5;
						}
						else if(total == 6) {
							if(tempTarget == "6")
								tempReward = bet->getAmount() * 7 / 6;
							else if(tempTarget == "hard6") {
								if(terminal->getFirst() == terminal->getSecond())
									tempReward = bet->getAmount() * 10;
								else
									remove = true;
							}
						}
						else if(total == 8) {
							if(tempTarget == "8")
								tempReward = bet->getAmount() * 7 / 6;
							else if(tempTarget == "hard8") {
								if(terminal->getFirst() == terminal->getSecond())
									tempReward = bet->getAmount() * 10;
								else
									remove = true;
							}
						}
						else if(total == 9) {
							if(tempTarget == "9")
								tempReward = bet->getAmount() * 7 / 5;
						}
						else if(total == 10) {
							if(tempTarget == "10")
								tempReward = bet->getAmount() * 9 / 5;
							else if(tempTarget == "hard10") {
								if(terminal->getFirst() == terminal->getSecond())
									tempReward = bet->getAmount() * 8;
								else
									remove = true;
							}
						}
					}


					// Lay Bet Removal
					if(total == 4 && tempTarget == "lay4") {
						remove = true;
					}
					else if(total == 5 && tempTarget == "lay5") {
						remove = true;
					}
					else if(total == 6 && tempTarget == "lay6") {
						remove = true;
					}
					else if(total == 8 && tempTarget == "lay8") {
						remove = true;
					}
					else if(total == 9 && tempTarget == "lay9") {
						remove = true;
					}
					else if(total == 10 && tempTarget == "lay10") {
						remove = true;
					}

					// One roll bets
					if(total == 2) {
						if(tempTarget == "2") {
							tempReward = bet->getAmount() * 31;
						}
						else if(tempTarget == "craps") {
							tempReward = bet->getAmount() * 8;
						}
						else if(tempTarget == "hilo") {
							tempReward = bet->getAmount() * 16;
						}
						else if(tempTarget == "field") {
							tempReward = bet->getAmount() * 3;
						}
						else if(tempTarget == "horn") {
							tempReward = bet->getAmount() * 17 / 2;
						}
					}
					else if(total == 12) {
						if(tempTarget == "12") {
							tempReward = bet->getAmount() * 31;
						}
						else if(tempTarget == "craps") {
							tempReward = bet->getAmount() * 8;
						}
						else if(tempTarget == "hilo") {
							tempReward = bet->getAmount() * 16;
						}
						else if(tempTarget == "field") {
							tempReward = bet->getAmount() * 3;
						}
						else if(tempTarget == "horn") {
							tempReward = bet->getAmount() * 17 / 2;
						}
					}
					else if(total == 3) {
						if(tempTarget == "3") {
							tempReward = bet->getAmount() * 16;
						}
						else if(tempTarget == "craps") {
							tempReward = bet->getAmount() * 8;
						}
						else if(tempTarget == "field") {
							tempReward = bet->getAmount() * 2;
						}
						else if(tempTarget == "horn") {
							tempReward = bet->getAmount() * 19 / 4;
						}
					}
					else if(total == 11) {
						if(tempTarget == "11") {
							tempReward = bet->getAmount() * 16;
						}
						else if(tempTarget == "field") {
							tempReward = bet->getAmount() * 2;
						}
						else if(tempTarget == "horn") {
							tempReward = bet->getAmount() * 19 / 4;
						}
					}
					else if(total == 4 || total == 9 || total == 10) {
						if(tempTarget == "field") {
							tempReward = bet->getAmount() * 2;
						}
					}
					else if(total == 7) {
						if(tempTarget == "7") {
							tempReward = bet->getAmount() * 5;
						}
						else if(tempTarget == "lay4" || tempTarget == "lay10") {
							tempReward = bet->getAmount() * 3 / 2;
							remove = true;
						}
						else if(tempTarget == "lay5" || tempTarget == "lay9") {
							tempReward = bet->getAmount() * 5 / 3;
							remove = true;
						}
						else if(tempTarget == "lay6" || tempTarget == "lay8") {
							tempReward = bet->getAmount() * 11 / 6;
							remove = true;
						}
					}

					if(tempTarget == "2" || tempTarget == "3" || tempTarget == "7" || tempTarget == "11" || tempTarget == "12" || tempTarget == "horn" || tempTarget == "field" || tempTarget == "craps" || tempTarget == "hilo") {
						remove = true;
					}


					if(tempReward > 0) {
						tempReward += winnings->get(bet->getPlayer());
						winnings->drop(bet->getPlayer());

						winnings->put(bet->getPlayer(), tempReward);
					}

					if(!remove) {
						remainingBets.add(bet);
					}
				}

				terminal->setBets(&remainingBets);

				// Handle button stuff
				// No button established
				if(terminal->getButton() < 4) {
					// set button
					if(total >= 4 && total <= 10 && total != 7) {
						terminal->setButton(total);
						terminal->notifyAll("The button is now on: " + String::valueOf(total));
					}
				}
				else {
					// button established
					if(total == terminal->getButton() || total == 7) {
						terminal->setButton(0);
					}
				}



				for (int i = 0; i < winnings->size(); ++i) { // send money and messages to players

					CreatureObject* player = winnings->elementAt(i).getKey();

					if (player != nullptr) {

						refreshCrapsMenu(player);

						if (winnings->get(i) == 0) {

							player->sendSystemMessage("You don't win anything");

						} else {

							Locker _locker(player);

							// Send message to others
							StringIdChatParameter textOther("gambling/default_interface","winner_to_other");
							textOther.setDI(winnings->get(i));
							textOther.setTO(player->getFirstName());
							textOther.setTO(player->getObjectID());
							terminal->notifyOthers(player, &textOther);

							StringIdChatParameter textPlayer("gambling/default_interface","winner_to_winner");
							textPlayer.setDI(winnings->get(i));
							player->sendSystemMessage(textPlayer);

							{
								TransactionLog trx(TrxCode::GAMBLINGCRAPS, player, winnings->get(i), true);
								player->addCashCredits(winnings->get(i), true);
							}
						}
					}
				}

				break;
			}
		}
	}
}

void GamblingManagerImplementation::leaveTerminal(CreatureObject* player, int machineType) {

	if (player != nullptr) {

		switch (machineType) {
			case GamblingTerminal::SLOTMACHINE: {

				ManagedReference<GamblingTerminal*> terminal = slotGames.get(player);

				if (terminal != nullptr) {

					Locker locker(terminal);

					if (terminal->getPlayersWindows()->contains(player)) {
						terminal->leaveTerminal(player);
						slotGames.drop(player);
					}
				}

				break;
			}
			case GamblingTerminal::ROULETTEMACHINE: {

				ManagedReference<GamblingTerminal*> terminal = rouletteGames.get(player);

				if (terminal != nullptr) {
					Locker locker(terminal);

					if (terminal->getPlayersWindows()->contains(player)) {
						terminal->leaveTerminal(player);
						rouletteGames.drop(player);
					}
				}

				break;
			}
			case GamblingTerminal::CRAPS: {

				ManagedReference<GamblingTerminal*> terminal = crapsGames.get(player);

				if (terminal != nullptr) {
					Locker locker(terminal);

					if (terminal->getPlayersWindows()->contains(player)) {
						pullCrapsBets(player);
						terminal->leaveTerminal(player);
						crapsGames.drop(player);
					}
				}

				break;
			}
		}

	}

}

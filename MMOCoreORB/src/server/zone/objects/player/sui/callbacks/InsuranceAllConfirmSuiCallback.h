/*
 * InsuranceAllConfirmSuiCallback.h
 *
 *  Created on: 01/13, 2012
 *      Author: Elvaron
 */

#ifndef INSURANCEALLCONFIRMSUICALLBACK_H_
#define INSURANCEALLCONFIRMSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "templates/params/OptionBitmask.h"
#include "server/zone/objects/transaction/TransactionLog.h"

class InsuranceAllConfirmSuiCallback : public SuiCallback {
public:
	InsuranceAllConfirmSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}

	void run(CreatureObject* player, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		if (!suiBox->isMessageBox() || cancelPressed || player == nullptr)
			return;

		ZoneServer* zoneServer = player->getZoneServer();

		int bank = player->getBankCredits();
		int cash = player->getCashCredits();

		int cost = 100;

		ManagedReference<SceneObject*> term = suiBox->getUsingObject().get();

		if (term == nullptr) {
			StringIdChatParameter params;
			params.setStringId("@ui:action_target_not_found_prose");
			params.setTT("@terminal_name:terminal_insurance");
			player->sendSystemMessage(params);
			return;
		}

		if (!player->isInRange(term, 15.0f)) {
			StringIdChatParameter params;
			params.setStringId("@container_error_message:container09_prose");
			params.setTT(term->getObjectName());
			player->sendSystemMessage(params);
			return;
		}

		PlayerManager* playerManager = player->getZoneServer()->getPlayerManager();

		Vector<ManagedReference<SceneObject*> > insurableItems = playerManager->getInsurableItems(player);

		if (insurableItems.size() == 0) {
			player->sendSystemMessage("@terminal_ui:no_uninsured_insurables");
			return;
		}

		int money = cash + bank;

		int j = 0;
		int totalcost = 0;
		bool finished = true;



		TransactionLog trxBank(player, TrxCode::INSURANCESYSTEM, 100 * insurableItems.size()); // Actual cost is set below

		for (int i = 0; i < insurableItems.size(); ++i) {
			SceneObject* obj = insurableItems.get(i);

			if (obj != nullptr && obj->isTangibleObject()) {

				TangibleObject* item = cast<TangibleObject*>( obj);

				cost = (item->getComplexity() * 5 * (2 - (item->getConditionDamage() / item->getMaxCondition())));

				if (cost > money) {
					StringIdChatParameter params;
					params.setStringId("@error_message:prose_nsf_insure");
					params.setTT(obj->getObjectName());
					player->sendSystemMessage(params);
					finished = false;
					break;
				}

				j++;

				Locker locker(item, player);

				uint32 bitmask = item->getOptionsBitmask();
				bitmask |= OptionBitmask::INSURED;
				item->setOptionsBitmask(bitmask);
				totalcost += cost;
				trxBank.addRelatedObject(obj->getObjectID());

			}
		}

		trxBank.addState("insuredCount", j);
		//cost *= j;

		if (bank < totalcost) {
			int diff = totalcost - bank;

			trxBank.setAmount(diff, true);
			player->subtractBankCredits(totalcost - diff);
			trxBank.commit();

			TransactionLog trxCash(player, TrxCode::INSURANCESYSTEM, totalcost - diff, true);
			trxCash.groupWith(trxBank);
			player->subtractCashCredits(diff);
		} else {
			trxBank.setAmount(totalcost, false);
			player->subtractBankCredits(totalcost);
		}

		if (finished) {
			player->sendSystemMessage("@base_player:insure_success");
		}
	}
};

#endif /* INSURANCEALLCONFIRMSUICALLBACK_H_ */

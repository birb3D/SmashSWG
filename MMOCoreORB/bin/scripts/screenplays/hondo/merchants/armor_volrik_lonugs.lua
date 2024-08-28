-- Legend of Hondo Merchant System
-- By R. Bassett Jr. (Tatwi) - www.tpot.ca
-- July 2015

local ObjectManager = require("managers.object.object_manager")

VolrikLonugsSP = ScreenPlay:new {
	numberOfActs = 1, 	
	relations = { 
		{name="meatlump", npcStanding=-9000, priceAdjust=15}, -- Adjust price only
		{name="townsperson", npcStanding=-9000, priceAdjust=12}, -- Adjust price only
	},
	goods = {
		{optName="vendor_loot", cost=1000, itemName="Some Stuff I Found", items={"vendor_loot"}}, 
		{optName="vendor_gear", cost=3500, itemName="Some Random Gear", items={"vendor_gear"}}, 
		{optName="vendor_tapes", cost=10000, itemName="An Armor/Clothing Attachment", items={"all_attachments"}}, 
	},
}


registerScreenPlay("VolrikLonugsSP", true)

function VolrikLonugsSP:start() 
	spawnMobile("naboo", "volrik_lonugs", 1, -5003, 6, 4263, 135, 0) -- naboo near bazaar terminals
end

volriklonugs_convo_handler = Object:new {
	tstring = "myconversation"
 }

function volriklonugs_convo_handler:getNextConversationScreen(conversationTemplate, conversingPlayer, selectedOption)
	nextConversationScreen = MerchantSystem:nextConvoScreenInnards(conversationTemplate, conversingPlayer, selectedOption, VolrikLonugsSP.relations, VolrikLonugsSP.goods)
	
	return nextConversationScreen
end

function volriklonugs_convo_handler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	conversationScreen = MerchantSystem:runScreenHandlerInnards(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen, VolrikLonugsSP.relations, VolrikLonugsSP.goods)
	
	return conversationScreen
end
-- Legend of Hondo Merchant System
-- By R. Bassett Jr. (Tatwi) - www.tpot.ca
-- July 2015

local ObjectManager = require("managers.object.object_manager")

NalYaroSP = ScreenPlay:new {
	numberOfActs = 1, 	
	relations = { 
		{name="jabba", npcStanding=3500, priceAdjust=5}, -- Friend
		{name="borvo", npcStanding=-4000, priceAdjust=5}, -- Enemy
		{name="valarian", npcStanding=-200, priceAdjust=10}, -- Enemy
		{name="hutt", npcStanding=-200, priceAdjust=10}, -- Enemy
	},
	goods = {
		{optName="vendor_loot", cost=1000, itemName="Some Stuff I Found", items={"vendor_loot"}}, 
		{optName="vendor_creature", cost=3000, itemName="Some Creature Stuff", items={"vendor_creature"}}, 
	},
}


registerScreenPlay("NalYaroSP", true)

function NalYaroSP:start() 
	spawnMobile("tatooine", "nal_yaro", 1, 3431, 5, -4883, 92, 0) -- Wayfar waypoint -5199 -6571
end

nalyaro_convo_handler = Object:new {
	tstring = "myconversation"
 }

function nalyaro_convo_handler:getNextConversationScreen(conversationTemplate, conversingPlayer, selectedOption)
	nextConversationScreen = MerchantSystem:nextConvoScreenInnards(conversationTemplate, conversingPlayer, selectedOption, NalYaroSP.relations, NalYaroSP.goods)
	
	return nextConversationScreen
end

function nalyaro_convo_handler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	conversationScreen = MerchantSystem:runScreenHandlerInnards(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen, NalYaroSP.relations, NalYaroSP.goods)
	
	return conversationScreen
end
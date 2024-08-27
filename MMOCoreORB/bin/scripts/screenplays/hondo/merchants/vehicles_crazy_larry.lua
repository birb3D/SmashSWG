-- Legend of Hondo Merchant System
-- By R. Bassett Jr. (Tatwi) - www.tpot.ca
-- July 2015

local ObjectManager = require("managers.object.object_manager")

CrazyLarry = ScreenPlay:new {
	numberOfActs = 1, 	
	relations = { 
		{name="nym", npcStanding=-9000, priceAdjust=15}, -- Adjust price only
		{name="lok_mercenaries", npcStanding=-9000, priceAdjust=5}, -- Adjust price only
		{name="bloodrazor", npcStanding=-1000, priceAdjust=20},  -- Enemy
		{name="canyon_corsair", npcStanding=-1000, priceAdjust=20}  -- Enemy
	},
	goods = {
		{optName="vendor_loot", cost=1000, itemName="Some Stuff I Found", items={"vendor_loot"}}, 
		{optName="vendor_strange", cost=5000, itemName="Random Strange Items", items={"strange_items"}}, 
	},
}


registerScreenPlay("CrazyLarry", true)
function CrazyLarry:start() 
	spawnMobile("tatooine", "crazylarry", 1, 14.5, -0.9, 20.7, 135, 1082879) -- mos eisley cantina
end

crazylarry_convo_handler = Object:new {
	tstring = "myconversation"
 }

function crazylarry_convo_handler:getNextConversationScreen(conversationTemplate, conversingPlayer, selectedOption)
	nextConversationScreen = MerchantSystem:nextConvoScreenInnards(conversationTemplate, conversingPlayer, selectedOption, CrazyLarry.relations, CrazyLarry.goods)
	
	return nextConversationScreen
end

function crazylarry_convo_handler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	conversationScreen = MerchantSystem:runScreenHandlerInnards(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen, CrazyLarry.relations, CrazyLarry.goods)
	
	return conversationScreen
end

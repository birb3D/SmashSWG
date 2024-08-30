-- Legend of Hondo Merchant System
-- By R. Bassett Jr. (Tatwi) - www.tpot.ca
-- July 2015

local ObjectManager = require("managers.object.object_manager")

CrazyLarry = ScreenPlay:new {
	numberOfActs = 1, 	
	relations = { 
		{name="jawa", npcStanding=100, priceAdjust=25}, -- Friends
		{name="tusken_raider", npcStanding=-2000, priceAdjust=10}, -- Enemy
	},
	goods = {
		{optName="vendor_loot", cost=1000, itemName="Some Stuff I Found", items={"vendor_loot"}}, 
		{optName="vendor_strange", cost=5000, itemName="Random Strange Items", items={"strange_items"}}, 
		{optName="item_craft_hack", cost=10000, itemName="Cr.4.ft Hacking Chip", items={"object/tangible/component/item/craft_hack.iff"}},
		{optName="item_scanner_jammer", cost=10000, itemName="Phantom SRS Jammer", items={"object/tangible/component/item/scanner_jammer.iff"}},
	},
}


registerScreenPlay("CrazyLarry", true)
function CrazyLarry:start() 
	spawnMobile("tatooine", "crazylarry", 1, 14.5, -0.9, 20.7, 135, 1256060) -- mos espa cantina
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

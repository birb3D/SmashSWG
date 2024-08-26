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
		{optName="gamba", cost=500, itemName="Customization Kit", items={"color_crystals"}}, 
		{optName="speederbike", cost=28000, itemName="Speederbike", items={"object/tangible/deed/vehicle_deed/speederbike_deed.iff"}},
		{optName="swoop", cost=45000, itemName="Swoop Bike", items={"object/tangible/deed/vehicle_deed/speederbike_swoop_deed.iff"}},
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


pistol_tangle = {
	minimumLevel = 0,
	maximumLevel = -1,
	customObjectName = "",
	directObjectTemplate = "object/weapon/ranged/pistol/pistol_tangle.iff",
	craftingValues = {
		{"mindamage",32,50,0},
		{"maxdamage",51,107,0},
		{"attackspeed",5.5,3.8,1},
		{"woundchance",2,4,1},
		{"roundsused",1,8,0},
		{"hitpoints",750,750,0},
		{"zerorange",0,0,0},
		{"zerorangemod",-5,-5,0},
		{"midrange",10,10,0},
		{"midrangemod",-10,-10,0},
		{"maxrange",48,48,0},
		{"maxrangemod",-80,-80,0},
		{"attackhealthcost",18,8,0},
		{"attackactioncost",33,18,0},
		{"attackmindcost",26,14,0},
	},
	customizationStringNames = {},
	customizationValues = {},

	-- randomDotChance: The chance of this weapon object dropping with a random dot on it. Higher number means less chance. Set to 0 to always have a random dot.
	randomDotChance = 625,
	junkDealerTypeNeeded = JUNKARMS,
	junkMinValue = 25,
	junkMaxValue = 45

}

addLootItemTemplate("pistol_tangle", pistol_tangle)

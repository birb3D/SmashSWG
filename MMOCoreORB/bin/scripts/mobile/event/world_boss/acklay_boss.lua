acklay_boss = Creature:new {
	customName = "Corrupted Acklay",
	socialGroup = "geonosian_creature",
	faction = "",
	level = 500,
	chanceHit = 70.0,
	damageMin = 500,
	damageMax = 1300,
	baseXp = 600549,
	baseHAM = 190000,
	baseHAMmax = 210000,
	--[[damageMin = 7570,
	damageMax = 9950,
	baseXp = 28549,
	baseHAM = 1680000,
	baseHAMmax = 1950000,]]--
	armor = 3,
	resists = {40,35,0,30,30,0,30,30,-1},
	meatType = "meat_carnivore",
	meatAmount = 1000,
	hideType = "hide_bristley",
	hideAmount = 950,
	boneType = "bone_mammal",
	boneAmount = 905,
	milk = 0,
	tamingChance = 0,
	ferocity = 30,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,
	scale = 1.5,

	templates = {"object/mobile/acklay_hue.iff"},
	lootGroups = {
		{
			groups = {
				{group = "strange_items", chance = 10000000}
			},
			lootChance = 10000000
		},
		{
			groups = {
				{group = "strange_items", chance = 10000000}
			},
			lootChance = 10000000
		},
		{
			groups = {
				{group = "strange_items", chance = 10000000}
			},
			lootChance = 10000000
		},

	},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"creatureareacombo","stateAccuracyBonus=100"},
		{"creatureareaknockdown","stateAccuracyBonus=100"},
		{"creatureareapoison","stateAccuracyBonus=90"}
	}
}

CreatureTemplates:addCreatureTemplate(acklay_boss, "acklay_boss")

rancor_boss = Creature:new {
	customName = "Corrupted Rancor",
	socialGroup = "rancor",
	faction = "",
	level = 500,
	chanceHit = 70.0,
	damageMin = 200,
	damageMax = 500,
	baseXp = 60549,
	baseHAM = 90000,
	baseHAMmax = 110000,
	armor = 3,
	resists = {35,85,65,85,85,85,65,85,60},
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

	templates = {"object/mobile/rancor.iff"},
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
		{"creatureareadisease","stateAccuracyBonus=90"},
		{"strongdisease",""}
	}
}

CreatureTemplates:addCreatureTemplate(rancor_boss, "rancor_boss")

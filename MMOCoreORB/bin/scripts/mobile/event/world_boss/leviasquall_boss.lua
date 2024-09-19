leviasquall_boss = Creature:new {
	customName = "The Killer Rabbit of Caerbannog",
	socialGroup = "squall",
	faction = "",
	level = 300,
	chanceHit = 70.0,
	damageMin = 500,
	damageMax = 1300,
	baseXp = 600549,
	baseHAM = 290000,
	baseHAMmax = 310000,
	armor = 3,
	resists = {40,35,0,30,30,0,30,30,-1},
	meatType = "meat_herbivore",
	meatAmount = 1500,
	hideType = "hide_bristley",
	hideAmount = 1500,
	boneType = "bone_mammal",
	boneAmount = 1500,
	milk = 0,
	tamingChance = 0,
	ferocity = 30,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = AIENABLED + INTERESTING,
	diet = CARNIVORE,
	scale = 9,

	templates = {"object/mobile/leviasquall.iff"},
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
		{"posturedownattack","stateAccuracyBonus=100"},
		{"creatureareacombo","stateAccuracyBonus=100"},
		{"stunattack","stateAccuracyBonus=100"},
		{"strongpoison",""},
		{"creatureareapoison",""},
		{"poisongascloud",""}
	}
}

CreatureTemplates:addCreatureTemplate(leviasquall_boss, "leviasquall_boss")

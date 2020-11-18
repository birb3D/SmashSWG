tanc_mite = Creature:new {
	objectName = "@mob/creature_names:tanc_mite",
	socialGroup = "mite",
	faction = "",
	level = 16,
	chanceHit = 0.31,
	damageMin = 130,
	damageMax = 150,
	baseXp = 960,
	baseHAM = 2300,
	baseHAMmax = 2900,
	armor = 0,
	resists = {110,0,0,0,0,0,0,-1,-1},
	meatType = "meat_insect",
	meatAmount = 4,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/tanc_mite_hue.iff"},
	hues = { 8, 9, 10, 11, 12, 13, 14, 15 },
	controlDeviceTemplate = "object/intangible/pet/tanc_mite_hue.iff",
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"intimidationattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(tanc_mite, "tanc_mite")

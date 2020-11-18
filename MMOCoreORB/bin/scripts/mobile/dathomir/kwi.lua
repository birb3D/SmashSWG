kwi = Creature:new {
	objectName = "@mob/creature_names:kwi",
	socialGroup = "kwi",
	faction = "",
	level = 20,
	chanceHit = 0.41,
	damageMin = 170,
	damageMax = 200,
	baseXp = 2037,
	baseHAM = 5200,
	baseHAMmax = 6800,
	armor = 0,
	resists = {25,25,25,180,25,25,-1,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 100,
	hideType = "hide_leathery",
	hideAmount = 85,
	boneType = "bone_mammal",
	boneAmount = 75,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 2,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/kwi_hue.iff"},
	hues = { 16, 17, 18, 19, 20, 21, 22, 23 },
	controlDeviceTemplate = "object/intangible/pet/kwi_hue.iff",
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"",""},
		{"intimidationattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(kwi, "kwi")

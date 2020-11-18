gackle_bat = Creature:new {
	objectName = "@mob/creature_names:gackle_bat",
	socialGroup = "gacklebat",
	faction = "",
	level = 16,
	chanceHit = 0.31,
	damageMin = 130,
	damageMax = 150,
	baseXp = 960,
	baseHAM = 2300,
	baseHAMmax = 2900,
	armor = 0,
	resists = {110,10,10,10,0,0,0,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 4,
	hideType = "hide_bristley",
	hideAmount = 2,
	boneType = "bone_mammal",
	boneAmount = 3,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/gackle_bat_hue.iff"},
	hues = { 0, 1, 2, 3, 4, 5, 6, 7 },
	controlDeviceTemplate = "object/intangible/pet/gackle_bat_hue.iff",
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"",""},
		{"intimidationattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(gackle_bat, "gackle_bat")

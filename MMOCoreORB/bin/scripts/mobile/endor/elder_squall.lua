elder_squall = Creature:new {
	objectName = "@mob/creature_names:elder_squall",
	socialGroup = "squall",
	faction = "",
	level = 16,
	chanceHit = 0.27,
	damageMin = 120,
	damageMax = 160,
	baseXp = 692,
	baseHAM = 1575,
	baseHAMmax = 1825,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 18,
	hideType = "hide_bristley",
	hideAmount = 12,
	boneType = "bone_mammal",
	boneAmount = 8,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {"object/mobile/squall_hue.iff"},
	hues = { 16, 17, 18, 19, 20, 21, 22, 23 },
	scale = 1.25,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(elder_squall, "elder_squall")

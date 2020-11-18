vampiric_gackle_bat = Creature:new {
	objectName = "@mob/creature_names:gackle_bat_vampiric",
	socialGroup = "gacklebat",
	faction = "",
	level = 18,
	chanceHit = 0.31,
	damageMin = 170,
	damageMax = 180,
	baseXp = 1160,
	baseHAM = 2900,
	baseHAMmax = 3500,
	armor = 0,
	resists = {110,10,10,10,10,10,10,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 4,
	hideType = "hide_bristley",
	hideAmount = 2,
	boneType = "bone_mammal",
	boneAmount = 3,
	milk = 0,
	tamingChance = 0.05,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/gackle_bat.iff"},
	controlDeviceTemplate = "object/intangible/pet/gackle_bat_hue.iff",
	scale = 1.05,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"intimidationattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(vampiric_gackle_bat, "vampiric_gackle_bat")

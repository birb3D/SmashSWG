pouncing_jax = Creature:new {
	objectName = "@mob/creature_names:pouncing_jax",
	socialGroup = "jax",
	faction = "",
	level = 15,
	chanceHit = 0.29,
	damageMin = 160,
	damageMax = 180,
	baseXp = 809,
	baseHAM = 2000,
	baseHAMmax = 2400,
	armor = 0,
	resists = {135,130,150,-1,-1,-1,-1,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 25,
	hideType = "hide_bristley",
	hideAmount = 35,
	boneType = "bone_mammal",
	boneAmount = 25,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/bearded_jax_hue.iff"},
	hues = { 24, 25, 26, 27, 28, 29, 30, 31 },
	controlDeviceTemplate = "object/intangible/pet/bearded_jax_hue.iff",
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"dizzyattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(pouncing_jax, "pouncing_jax")

lowland_brackaset = Creature:new {
	objectName = "@mob/creature_names:brackaset_lowlands",
	socialGroup = "brackaset",
	faction = "",
	mobType = MOB_HERBIVORE,
	level = 20,
	chanceHit = 0.35,
	damageMin = 170,
	damageMax = 200,
	baseXp = 2037,
	baseHAM = 5200,
	baseHAMmax = 6800,
	armor = 0,
	resists = {135,130,10,10,-1,-1,10,10,-1},
	meatType = "meat_wild",
	meatAmount = 75,
	hideType = "hide_leathery",
	hideAmount = 65,
	boneType = "bone_mammal",
	boneAmount = 60,
	milkType = "milk_wild",
	milk = 65,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = HERD,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {"object/mobile/brackaset_hue.iff"},
	hues = { 8, 9, 10, 11, 12, 13, 14, 15 },
	controlDeviceTemplate = "object/intangible/pet/brackaset_hue.iff",
	scale = 0.9,
	lootGroups = {
		{
			groups = {
				{group = "brackaset_common", chance = 10000000}
			},
			lootChance = 200000
		}
	},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "unarmed",
	secondaryWeapon = "none",
	conversationTemplate = "",
	
	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = {},
	secondaryAttacks = { }
}

CreatureTemplates:addCreatureTemplate(lowland_brackaset, "lowland_brackaset")

droideka_boss = Creature:new {
	customName = "M1r.d3r Experimental Attack Droid",
	socialGroup = "droideka",
	faction = "",
	level = 500,
	chanceHit = 70.0,
	damageMin = 100,
	damageMax = 400,
	baseXp = 28549,
	baseHAM = 10000,
	baseHAMmax = 15000,
	--[[damageMin = 7570,
	damageMax = 9950,
	baseXp = 28549,
	baseHAM = 1680000,
	baseHAMmax = 1950000,]]--
	armor = 3,
	resists = {40,40,30,0,30,0,30,-1,20},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,
	scale = 3.0,

	templates = {"object/mobile/droideka.iff"},
	lootGroups = {
		{
	        groups = {
				{group = "worldboss_common", chance = 10000000},
			},
			lootChance = 10000000
		},
		{
			groups = {
				{group = "worldboss_rare", chance = 10000000}
			},
			lootChance = 10000000
		},
		{
			groups = {
				{group = "worldboss_legendary", chance = 10000000}
			},
			lootChance = 10000000
		},
	},
	conversationTemplate = "",
	weapons = {},
	defaultWeapon = "object/weapon/ranged/droid/droid_droideka_ranged.iff",
	defaultAttack = "attack",
	attacks = {
		{"creatureareacombo","stateAccuracyBonus=100"},
		{"creatureareaknockdown","stateAccuracyBonus=100"},
		{"creatureareapoison","stateAccuracyBonus=90"}
	}
}

CreatureTemplates:addCreatureTemplate(droideka_boss, "droideka_boss")

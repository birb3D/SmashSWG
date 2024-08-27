vendor_creature = {
	description = "",
	minimumLevel = 0,
	maximumLevel = 0,
	lootItems = {

		{groupTemplate = "resource_creature", weight = 3500000}, -- 35%

		-- 51%
		{groupTemplate = "brackaset_common", weight = 850000},
		{groupTemplate = "fambaa_common", weight = 850000},
		{groupTemplate = "gurk_king_common", weight = 850000},
		{groupTemplate = "harrower_bone", weight = 850000},
		{groupTemplate = "sharnaff_common", weight = 850000},
		{groupTemplate = "kliknik_common", weight = 850000},

		-- 13.2%
		{groupTemplate = "krayt_tissue_uncommon", weight = 220000},
		{groupTemplate = "peko_albatross", weight = 220000},
		{groupTemplate = "rancor_common", weight = 220000},
		{groupTemplate = "kimogila_common", weight = 220000},
		{groupTemplate = "voritor_lizard_common", weight = 220000},
		{groupTemplate = "giant_dune_kimo_common", weight = 220000},

		-- 0.75%
		{groupTemplate = "krayt_dragon_common", weight = 25000},
		{groupTemplate = "krayt_dragon_common2", weight = 25000},
		{groupTemplate = "krayt_tissue_rare", weight = 25000},

		-- 0.05%
		{groupTemplate = "krayt_pearls", weight = 5000},

	}
}

addLootGroupTemplate("vendor_creature", vendor_creature)

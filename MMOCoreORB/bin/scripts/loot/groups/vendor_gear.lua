vendor_gear = {
	description = "",
	minimumLevel = 0,
	maximumLevel = 0,
	lootItems = {

		-- Weapons (40% chance)
		{groupTemplate = "weapons_all", weight = 4000000},

		-- Armors (40% chance)
		{groupTemplate = "armor_all", weight = 4000000},

		-- Clothing (20% chance)
		{groupTemplate = "wearables_all", weight = 2000000},

	}
}

addLootGroupTemplate("vendor_gear", vendor_gear)

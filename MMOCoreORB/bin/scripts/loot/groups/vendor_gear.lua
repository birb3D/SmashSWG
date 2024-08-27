vendor_gear = {
	description = "",
	minimumLevel = 0,
	maximumLevel = 0,
	lootItems = {

		{groupTemplate = "looted_container", weight = 1000000}, 
		-- Weapons (30% chance)
		{groupTemplate = "weapons_all", weight = 3000000},

		-- Armors (30% chance)
		{groupTemplate = "armor_all", weight = 3000000},

		-- Clothing (30% chance)
		{groupTemplate = "wearables_all", weight = 3000000},

	}
}

addLootGroupTemplate("vendor_gear", vendor_gear)

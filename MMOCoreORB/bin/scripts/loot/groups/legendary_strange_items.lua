legendary_strange_items = {
	description = "",
	minimumLevel = 0,
	maximumLevel = 0,
	lootItems = {

		{groupTemplate = "resource_large_chemical", weight = 142857},
		{groupTemplate = "resource_large_flora", weight = 142857},
		{groupTemplate = "resource_large_gemstone", weight = 142857},
		{groupTemplate = "resource_large_metal", weight = 142857},
		{groupTemplate = "resource_large_ore", weight = 142857},
		{groupTemplate = "resource_large_water", weight = 142857}, 
		{groupTemplate = "resource_large_creature", weight = 142857},


		-- 15.95%
		{groupTemplate = "looted_container", weight = 1595001}, 

		-- 10%
		{groupTemplate = "color_crystals", weight = 1000000}, 

		-- 64%
		{itemTemplate = "legendary_strange_biologic_effect_controller", weight = 680000}, -- Weighted more heavily because only one for this class
		{itemTemplate = "legendary_strange_armor_segment_bone", weight = 260000},
		{itemTemplate = "legendary_strange_armor_segment_zam", weight = 260000},
		{itemTemplate = "legendary_strange_armor_segment_chitin", weight = 260000},
		{itemTemplate = "legendary_strange_armor_segment_padded", weight = 260000},
		{itemTemplate = "legendary_strange_armor_segment_ubese", weight = 260000},
		{itemTemplate = "legendary_strange_armor_segment_tantel", weight = 260000},
		{itemTemplate = "legendary_strange_bio_component_food_light", weight = 260000},
		{itemTemplate = "legendary_strange_bio_component_food_medium", weight = 260000},
		{itemTemplate = "legendary_strange_bio_component_food_heavy", weight = 260000},
		{itemTemplate = "legendary_strange_scope_weapon_advanced", weight = 260000},
		{itemTemplate = "legendary_strange_sword_core_advanced", weight = 260000},
		{itemTemplate = "legendary_strange_reinforcement_core_advanced", weight = 260000},
		{itemTemplate = "legendary_strange_vibro_unit_advanced", weight = 260000},
		{itemTemplate = "legendary_strange_stock_advanced", weight = 260000},
		{itemTemplate = "legendary_strange_droid_combat_module_slow", weight = 260000},
		{itemTemplate = "legendary_strange_droid_combat_module_fast", weight = 260000},
		{itemTemplate = "legendary_strange_structure_fluidic_drilling_pumping_unit", weight = 260000},
		{itemTemplate = "legendary_strange_structure_harvesting_mechanism", weight = 260000},
		{itemTemplate = "legendary_strange_structure_heavy_harvesting_mechanism", weight = 260000},
		{itemTemplate = "legendary_strange_structure_light_ore_mining_unit", weight = 260000},
		{itemTemplate = "legendary_strange_structure_ore_mining_unit", weight = 260000},
		{itemTemplate = "legendary_strange_structure_turbo_fluidic_drilling_pumping_unit", weight = 260000},

		-- 0.05%
		{itemTemplate = "speederbike_swoop_deed", weight = 5000},
	}
}

addLootGroupTemplate("strange_items", strange_items)

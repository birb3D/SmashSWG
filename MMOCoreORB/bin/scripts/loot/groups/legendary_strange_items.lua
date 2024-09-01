legendary_strange_items = {
	description = "",
	minimumLevel = 0,
	maximumLevel = 0,
	lootItems = {
		{itemTemplate = "legendary_strange_biologic_effect_controller", weight = 760000}, -- Weighted more heavily because only one for this class
		{itemTemplate = "legendary_strange_armor_segment_bone", weight = 380000},
		{itemTemplate = "legendary_strange_armor_segment_zam", weight = 380000},
		{itemTemplate = "legendary_strange_armor_segment_chitin", weight = 380000},
		{itemTemplate = "legendary_strange_armor_segment_padded", weight = 380000},
		{itemTemplate = "legendary_strange_armor_segment_ubese", weight = 380000},
		{itemTemplate = "legendary_strange_armor_segment_tantel", weight = 380000},
		{itemTemplate = "legendary_strange_bio_component_food_light", weight = 380000},
		{itemTemplate = "legendary_strange_bio_component_food_medium", weight = 380000},
		{itemTemplate = "legendary_strange_bio_component_food_heavy", weight = 380000},
		{itemTemplate = "legendary_strange_scope_weapon_advanced", weight = 380000},
		{itemTemplate = "legendary_strange_sword_core_advanced", weight = 380000},
		{itemTemplate = "legendary_strange_reinforcement_core_advanced", weight = 380000},
		{itemTemplate = "legendary_strange_vibro_unit_advanced", weight = 380000},
		{itemTemplate = "legendary_strange_stock_advanced", weight = 380000},
		{itemTemplate = "legendary_strange_droid_combat_module_slow", weight = 380000},
		{itemTemplate = "legendary_strange_droid_combat_module_fast", weight = 380000},
		{itemTemplate = "legendary_strange_structure_fluidic_drilling_pumping_unit", weight = 380000},
		{itemTemplate = "legendary_strange_structure_harvesting_mechanism", weight = 380000},
		{itemTemplate = "legendary_strange_structure_heavy_harvesting_mechanism", weight = 380000},
		{itemTemplate = "legendary_strange_structure_light_ore_mining_unit", weight = 380000},
		{itemTemplate = "legendary_strange_structure_ore_mining_unit", weight = 380000},
		{itemTemplate = "legendary_strange_structure_turbo_fluidic_drilling_pumping_unit", weight = 380000},

		-- 5%
		{itemTemplate = "speederbike_swoop_deed", weight = 500000},
	}
}

addLootGroupTemplate("legendary_strange_items", legendary_strange_items)

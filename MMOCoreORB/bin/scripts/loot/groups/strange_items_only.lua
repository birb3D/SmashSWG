strange_items_only = {
	description = "",
	minimumLevel = 0,
	maximumLevel = 0,
	lootItems = {

		{itemTemplate = "strange_biologic_effect_controller", weight = 833349}, -- Weighted more heavily because only one for this class
		{itemTemplate = "strange_armor_segment_bone", weight = 416666},
		{itemTemplate = "strange_armor_segment_zam", weight = 416666},
		{itemTemplate = "strange_armor_segment_chitin", weight = 416666},
		{itemTemplate = "strange_armor_segment_padded", weight = 416666},
		{itemTemplate = "strange_armor_segment_ubese", weight = 416666},
		{itemTemplate = "strange_armor_segment_tantel", weight = 416666},
		{itemTemplate = "strange_bio_component_food_light", weight = 416666},
		{itemTemplate = "strange_bio_component_food_medium", weight = 416666},
		{itemTemplate = "strange_bio_component_food_heavy", weight = 416666},
		{itemTemplate = "strange_scope_weapon_advanced", weight = 416666},
		{itemTemplate = "strange_sword_core_advanced", weight = 416666},
		{itemTemplate = "strange_reinforcement_core_advanced", weight = 416666},
		{itemTemplate = "strange_vibro_unit_advanced", weight = 416666},
		{itemTemplate = "strange_stock_advanced", weight = 416666},
		{itemTemplate = "strange_droid_combat_module_slow", weight = 416666},
		{itemTemplate = "strange_droid_combat_module_fast", weight = 416666},
		{itemTemplate = "strange_structure_fluidic_drilling_pumping_unit", weight = 416666},
		{itemTemplate = "strange_structure_harvesting_mechanism", weight = 416666},
		{itemTemplate = "strange_structure_heavy_harvesting_mechanism", weight = 416666},
		{itemTemplate = "strange_structure_light_ore_mining_unit", weight = 416666},
		{itemTemplate = "strange_structure_ore_mining_unit", weight = 416666},
		{itemTemplate = "strange_structure_turbo_fluidic_drilling_pumping_unit", weight = 416666},

	}
}

addLootGroupTemplate("strange_items_only", strange_items_only)

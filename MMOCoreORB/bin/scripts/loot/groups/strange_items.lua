strange_items = {
	description = "",
	minimumLevel = 0,
	maximumLevel = 0,
	lootItems = {

		-- 27%
		{groupTemplate = "resource_chemical", weight = 385714}, 
		{groupTemplate = "resource_flora", weight = 385714}, 
		{groupTemplate = "resource_gemstone", weight = 385714}, 
		{groupTemplate = "resource_metal", weight = 385714}.
		{groupTemplate = "resource_ore", weight = 385714},
		{groupTemplate = "resource_water", weight = 385714}, 
		{groupTemplate = "resource_creature", weight = 385714}, 


		-- 25.95%
		{groupTemplate = "looted_container", weight = 2595002}, 

		-- 15%
		{groupTemplate = "color_crystals", weight = 1500000}, 

		-- 32%
		{itemTemplate = "strange_biologic_effect_controller", weight = 340000}, -- Weighted more heavily because only one for this class
		{itemTemplate = "strange_armor_segment_bone", weight = 130000},
		{itemTemplate = "strange_armor_segment_zam", weight = 130000},
		{itemTemplate = "strange_armor_segment_chitin", weight = 130000},
		{itemTemplate = "strange_armor_segment_padded", weight = 130000},
		{itemTemplate = "strange_armor_segment_ubese", weight = 130000},
		{itemTemplate = "strange_armor_segment_tantel", weight = 130000},
		{itemTemplate = "strange_bio_component_food_light", weight = 130000},
		{itemTemplate = "strange_bio_component_food_medium", weight = 130000},
		{itemTemplate = "strange_bio_component_food_heavy", weight = 130000},
		{itemTemplate = "strange_scope_weapon_advanced", weight = 130000},
		{itemTemplate = "strange_sword_core_advanced", weight = 130000},
		{itemTemplate = "strange_reinforcement_core_advanced", weight = 130000},
		{itemTemplate = "strange_vibro_unit_advanced", weight = 130000},
		{itemTemplate = "strange_stock_advanced", weight = 130000},
		{itemTemplate = "strange_droid_combat_module_slow", weight = 130000},
		{itemTemplate = "strange_droid_combat_module_fast", weight = 130000},
		{itemTemplate = "strange_structure_fluidic_drilling_pumping_unit", weight = 130000},
		{itemTemplate = "strange_structure_harvesting_mechanism", weight = 130000},
		{itemTemplate = "strange_structure_heavy_harvesting_mechanism", weight = 130000},
		{itemTemplate = "strange_structure_light_ore_mining_unit", weight = 130000},
		{itemTemplate = "strange_structure_ore_mining_unit", weight = 130000},
		{itemTemplate = "strange_structure_turbo_fluidic_drilling_pumping_unit", weight = 130000},

		-- 0.05%
		{itemTemplate = "speederbike_swoop", weight = 5000},

	}
}

addLootGroupTemplate("strange_items", strange_items)

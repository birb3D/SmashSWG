strange_biologic_effect_controller = {
	minimumLevel = 0,
	maximumLevel = -1,
	customObjectName = "Strange Advanced Biological Effect Controller",
	directObjectTemplate = "object/tangible/component/chemistry/biologic_effect_controller_advanced.iff",
	craftingValues = {
		{"power", 60,160,0},
		{"charges", -100,-100,0},
		{"useCount",1,8,0}
	},
	customizationStringName = {},
	customizationValues = {}
}


addLootItemTemplate("strange_biologic_effect_controller", strange_biologic_effect_controller)

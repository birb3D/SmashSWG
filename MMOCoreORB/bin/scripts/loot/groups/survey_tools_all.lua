survey_tools_all = {
	description = "",
	minimumLevel = 0,
	maximumLevel = 0,
	lootItems = {
		{itemTemplate = "survey_tool_gas", weight = 5000000},
		{itemTemplate = "survey_tool_inorganic.lua", weight = 5000000},
		{itemTemplate = "survey_tool_liquid.lua", weight = 5000000},
		{itemTemplate = "survey_tool_lumber.lua", weight = 5000000},
		{itemTemplate = "survey_tool_mineral.lua", weight = 5000000},
		{itemTemplate = "survey_tool_moisture.lua", weight = 5000000},
		{itemTemplate = "survey_tool_organic.lua", weight = 5000000},
		{itemTemplate = "survey_tool_solar.lua", weight = 5000000},
		{itemTemplate = "survey_tool_wind.lua", weight = 5000000},

	}
}

addLootGroupTemplate("survey_tools_all", survey_tools_all)
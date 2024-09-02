NabooMoeniaScreenPlay = CityScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "NabooMoeniaScreenPlay",

	planet = "naboo",

	gcwMobs = {
		--rebel 'stronghold' spawns
		{"specforce_marine", 4794.6, 4.2, -4700, 50, 0, "", true},
		{"specforce_marine", 4799.2, 4.2, -4693, -150, 0, "", true},
		{"specforce_infiltrator", 4835.9, 4.1, -4732.2, -20, 0, "", true},
		{"specforce_infiltrator", 4841.1, 4.1, -4730.3, -20, 0, "", true},
		{"rebel_specforce_pathfinder", 4829.9, 4.2,-4578.6, -13, 0, "", true},
		{"rebel_specforce_pathfinder", 4832.0, 4.2, -4572.0, 80, 0, "", true},
		{"specforce_infiltrator", 4864.0, 3.8, -4788.6, 160, 0, "", true},
		{"specforce_infiltrator", 4858.2, 3.8, -4790.8, 160, 0, "", true},
		{"specforce_marine", 4826.3, 4.3, -4866.8, 80, 0, "", true},
		{"specforce_marine", 4825.2, 4.3, -4861.2, 80, 0, "", true},
		{"specforce_infiltrator", 4804.7, 4.3, -4844.9, -2, 0, "", true},
		{"specforce_infiltrator", 4799.1, 4.3, -4845.6, -12, 0, "", true},
		{"specforce_marine", 4695.3, 3.8, -4873.9, 0, 0, "", true},
		{"specforce_marine", 4695.7, 3.8, -4913.5, 180, 0, "", true},
		{"rebel_specforce_pathfinder", 4707.1, 3.8, -4894.6, 90, 0, "", true},
	},

	patrolNpcs = {"businessman_patrol", "commoner_fat_patrol", "commoner_naboo_patrol", "commoner_old_patrol", "commoner_patrol", "commoner_technician_patrol", "naboo_nomad_patrol", "noble_patrol", "official_patrol", "scientist_patrol"},

	patrolMobiles = {
		--{patrolPoints, template, x, z, y, direction, cell, mood, combatPatrol},
		{"npc_1", "patrolNpc", 4795, 4, -4722, 45, 0, "", false},
		{"npc_2", "patrolNpc", 4825, 4, -4679, 180, 0, "", false},
		{"npc_3", "patrolNpc", 4852, 4, -4677, 255, 0, "", false},

		--Cantina
		{"cantina_1", "r3", 6.0, -0.894992 , 7.2, 100, 111, "", false},
		{"cantina_2", "patrolNpc", 8, -0.894992 , -8.7, 100, 111, "playful", false},
		{"cantina_3", "surgical_droid_21b", -5.11,-0.894992,6.8, 300, 111, "conversation", false},
		{"cantina_4", "patrolNpc", -7.2,-0.894992,-6, 300, 111, "conversation", false},
		{"cantina_5", "patrolNpc", 21.32,-0.894992,10.47, 300, 111, "happy", false},
		{"cantina_6", "patrolNpc", -4.11,-0.894992,7, 300, 111, "happy", false},
		{"cantina_7", "patrolNpc", 40.13, 0.1, 1.47, 300, 109, "playful", false},
		{"cantina_8", "patrolNpc", 14.3, -0.894992, 2, 200, 111, "playful", false},
		{"cantina_9", "patrolNpc", 41.73, 0.1, 0, 40, 109, "playful", false},

		--Starport
		{"starport_walk_1", "patrolNpc", -4.61669,0.639424,50.7263, 40, 4215410, "playful", false},
		{"starport_walk_1", "patrolNpc", -4.61669,0.639424,51.7263, 40, 4215410, "playful", false},
		{"starport_walk_3", "r3", -4.61669,0.639424,52.7263, 40, 4215410, "playful", false},
		{"starport_walk_3", "patrolNpc", -4.61669,0.639424,53.7263, 40, 4215410, "playful", false},
		{"starport_walk_2", "patrolNpc", -0.61669,0.639424,50.7263, 40, 4215410, "playful", false},
		{"starport_walk_2", "patrolNpc", -0.61669,0.639424,51.7263, 40, 4215410, "playful", false},
		{"starport_walk_4", "patrolNpc", -0.61669,0.639424,52.7263, 40, 4215410, "playful", false},
		{"starport_walk_4", "surgical_droid_21b", -0.61669,0.639424,53.7263, 40, 4215410, "playful", false},
	},

	patrolPoints = {
		--table_name = {{x, z, y, cell, delayAtNextPoint}}
		npc_1 = {{4795, 4, -4722, 0, true}, {4770, 4, -4731, 0, true}, {4759, 4, -4750, 0, true},  {4751, 4, -4730, 0, true}},
		npc_2 = {{4825, 4, -4679, 0, true}, {4819, 4, -4658, 0, true}, {4831, 4, -4669, 0, true}, {4831, 4, -4649, 0, true}},
		npc_3 = {{4852, 4, -4677, 0, true}, {4849, 4, -4711, 0, true}, {4840, 4, -4699, 0, true}, {4846, 4, -4672, 0, true}},

		cantina_1 = {{7, -0.894992 , 7.2, 111, false}, {16, -0.894992 , 0, 111, false}, {5, -0.894992 , -7, 111, false}, {16, -0.894992 , 0, 111, false}},
		cantina_2 = {{5, -0.894992 , -9, 111, false}, {3, -0.894992 , -5.4, 111, false}, {12, -0.894992 , -6, 111, false}, {10, -0.894992 , -11, 111, false}},
		cantina_3 = {{-5.11,-0.894992,5, 111, false}, {-5.11,-0.894992,6.4, 111, false}, {0,-0.894992,6.4, 111, false}, {0,-0.894992,5, 111, 111, true}, {-1.51,-0.894992,6.4, 111, false}, {-7.11,-0.894992,6.4, 111, false}},
		cantina_4 = {{-7.2,-0.894992,-5, 111, false}, {-7.2,-0.894992,-6.4, 111, false}, {-4.3,-0.894992,-6.4, 111, false}, {-4.3,-0.894992,-5, 111, 111, false}, {-4.3,-0.894992,-6.4, 111, false}, {-7.2,-0.894992,-6.4, 111, false}, {-8.2,-0.894992,-11.4, 111, false}},
		cantina_5 = {{23.32,-0.894992,10.47, 111, false}, {21,-0.894992,-8.47, 111, false}, {20, -0.894992 , -1.4, 111, true}},
		cantina_6 = {{-2.11,-0.894992,7, 111, true}, {23,-0.894992,11, 111, false}, {19.5, -0.9, 18.7, 8105498, false}},
		cantina_7 = {{16, -0.894992 , 0, 111, true}, {17, -0.894992 , 0, 111, false}, {39.13, 0.1, 1.27, 109, true}},
		cantina_8 = {{16.3, -0.894992 , 2, 111, true}, {17.3, -0.894992 , 2, 111, false}, {42.73, 0.1, 2.47, 109, true}},
		cantina_9 = {{23, -0.894992 , -1.2, 111, false}, {41.73, 0.1, 0, 109, true}},

		starport_walk_1 = {{-4.61669,0.639424,50.7263,4215410, false}, {4709,5,-4692, false}, {4709,5,-4654, false}},
		starport_walk_2 = {{-0.61669,0.639424,50.7263,4215410, false}, {4709,5,-4692, false}, {4709,5,-4651, false}},
		starport_walk_3 = {{-4.61669,0.639424,50.7263,4215410, false}, {4709,5,-4692, false}, {4709,5,-4648, false}},
		starport_walk_4 = {{-0.61669,0.639424,50.7263,4215410, false}, {4709,5,-4692, false}, {4709,5,-4645, false}},
	},

	stationaryCommoners = {"commoner", "commoner_fat", "commoner_naboo", "commoner_old"},
	stationaryNpcs = {"agriculturalist", "artisan", "bodyguard", "bothan_diplomat", "bounty_hunter", "businessman", "commoner_technician", "contractor", "entertainer", "explorer", "farmer", "farmer_rancher", "fringer",
				"gambler", "info_broker", "medic", "mercenary", "miner", "naboo_nomad", "noble", "official", "patron_ishitib", "pilot", "rancher", "scientist", "slicer", "traveller"},

	--{respawn, x, z, y, direction, cell, mood}
	stationaryMobiles = {
		{1, 4667.6, 3.8, -4785.3, -20, 0, ""},
		{1, 4667.9, 3.8, -4783.4, 170, 0, ""},
		{1, 4646.5, 3.2, -4796.9, -179, 0, "fishing"},
	},

	mobiles = {
		--starport interior
		{"pilot",60,-5.7,0.6,67.4,0,4215410, "sad"},
		{"chassis_dealer",60,-4.3,0.6,67.6,-99,4215410, "conversation"},
		{"commoner_naboo",60,52.8,-0.5,42.3,70,4215413, "sad"},
		{"medic",60,54.4,-0.5,42.7,-120,4215413, "npc_consoling"},
		{"trainer_shipwright",60,-0.4,0.6,67.1,-177,4215410, "neutral"},

		{"informant_npc_lvl_1",0,4652,3.8,-4749,0,0, ""},
		{"informant_npc_lvl_1",0,4744,3.8,-4847,0,0, ""},
		{"informant_npc_lvl_1",0,4825,3.8,-4829, 235,0, ""},
		{"informant_npc_lvl_1",0,4958,3.8,-4854,0,0, ""},
		{"informant_npc_lvl_1",0,4976,3.8,-4920,0,0, ""},
		{"informant_npc_lvl_1",0,4971,3.8,-4941,0,0, ""},
		{"informant_npc_lvl_1",0,4909,3.8,-4975,0,0, ""},
		{"informant_npc_lvl_1",0,4679,3.8,-4923,0,0, ""},
		{"informant_npc_lvl_1",0,4838,4.4,-4877,0,0, ""},
		{"informant_npc_lvl_1",0,4810,4.2,-4627,0,0, ""},
		{"informant_npc_lvl_1",0,4773,4.4,-4937,0,0, ""},
		{"informant_npc_lvl_2",0,4638,4.4,-4643,270,0, ""},
		{"informant_npc_lvl_3",0,4721,4.2,-4614,180,0, ""},
		{"rebel_recruiter",0,4826,4.2,-4696,-93,0, ""},
		{"trainer_architect",0,4779,3.75,-4973,0,0, ""},
		{"trainer_artisan",0,4823.13,4.17,-4705.34,81,0, ""},
		{"trainer_brawler",0,4800,4.17,-4734,151,0, ""},
		{"trainer_brawler",0,4999,3.8,-4926,-12,0, ""},
		{"trainer_chef",0,4942,3.8,-4837,180,0, ""},
		{"trainer_dancer",0,4730,3.75,-4872,44,0, ""},
		{"trainer_doctor",0,4887,3.8,-4899,180,0, ""},
		{"trainer_droidengineer",0,4654,4.3,-4692,0,0, ""},
		{"trainer_entertainer",0,4846,4.17,-4658,258,0, ""},
		{"trainer_marksman",0,4794,4.17,-4730,0,0, ""},
		{"trainer_medic",0,4808,4.17,-4724,0,0, ""},
		{"trainer_medic",0,4772,3.7,-4814,164,0, ""},
		{"trainer_merchant",0,4819,4.17,-4704,81,0, ""},
		{"trainer_musician",0,4740,3.8,-4886,0,0, ""},
		{"trainer_scout",0,4836.08,4.17,-4703.96,94,0, ""},
		{"trainer_squadleader",0,4701,3.75,-4939,0,0, ""},
		{"trainer_tailor",0,4858,3.8,-4799,180,0, ""},
		{"junk_lila", 0, 26, -0.9, 11.4, -128, 111, ""},
		{"junk_dealer", 0, -14.4, 1.1, 3.2, 122, 1717532, ""},
		{"junk_dealer", 0, 4810.44, 4.17, -4663.38, 112, 0, ""},

		--Cantina
		{"informant_npc_lvl_2",0,-2.2226,-0.894992,5.90785,90,111, "happy"},
		-- 1 person far left side of the bar in the back
		{"dorn_gestros",60,-6.00754,-0.894992,-5.35219,231.068,111, "calm"},
		-- 2 people talking in front of the bar slightly right
		{"medic",60,12.1732,-0.894991,3.93609,180.003,111, "conversation"},
		{"sullustan_male",300,12.1732,-0.894992,2.93609,360.011,111, "conversation"},
		-- 4 commoners standing next to bar right front 
		{"farmer_rancher",60,3.11,0,5.4,161.005,111, "bored"},
		{"artisan",60,1.11,0,5.4,330.024,111, "npc_standing_drinking"},
		{"info_broker",60,-3.11,0,5.4,16.6733,111, "npc_standing_drinking"},
		{"commoner_tatooine",60,4.11,-0.894992,5.4,158.443,111, "npc_standing_drinking"},
		-- Corner Music Guys By Door
		{"doikk_nats",60,20.32,-0.894992,2.47,200.0013,111, "themepark_music_3"},
		{"figrin_dan",60,21.69,-0.894992,0.4,-40,111, "themepark_music_3"},
	    {"nalan_cheel",60,19.54,-0.894992,-1.13,40.0011,111, "themepark_music_1"},
		-- 3 People Talking far left side of bar center aisle 
		{"bounty_hunter",300,3.61201,-0.894992,-8.73417,135.006,111, "conversation"},
		{"farmer_rancher",60,4.71201,-0.894992,-9.83418,360.011,111, "conversation"},
		{"entertainer",300,4.71201,-0.894992,-8.73417,180.01,111, "conversation"},
		-- 2 patron_chiss left side against the bar
		{"patron_chiss",60,3.62,-0.894992,-4.77,184.005,111, "sad"},
		{"patron_chiss",60,1.74,-0.894992,-4.91,95.0028,111, "npc_consoling"},
		-- Far left cell nearest to door 2 people talking
		{"corellia_times_investigator", 300, 20.6, -0.9, -18.6, 180, 112, "conversation"},
		{"commoner_technician", 300, 20.6, -0.9, -19.6, 0, 112, "conversation"},
		-- 3 people talking far right cell closest to the door
		{"brawler", 60, 22.6, -0.9, 19.6, 0, 113, "npc_consoling"},
		{"commoner", 60, 21.5, -0.9, 20.7, 135, 113, "sad"},
		{"farmer_rancher", 300, 22.6, -0.9, 20.7, 180, 113, "npc_consoling"},
		-- 2 people talking left middle cell
		{"bounty_hunter",300,2.1656,-0.894992,-15.9672,360.011,114, "calm"},
		{"contractor",60,2.1656,-0.894992,-14.9672,180.001,114, "conversation"},
		--1 person far right middle cell
		{"businessman",60,0.978477,-0.894992,21.4841,311.517,115, "angry"},
		-- 1 person far left back cell 
		{"mercenary",300,-5.02826,-0.894991,-21.3375,-20,116, "calm"},
		-- Borvo's Guard in right room just behind bar
		{"rebel_recruiter",0,-29,-0.89,-1.2,74,119, "npc_standing_drinking"},
		-- 2 people talking in right room just behind the bar
		{"commoner_tatooine",60,-20.6545,-0.894989,25.0112,0,120, "conversation"},
		{"noble",300,-20.6545,-0.894989,26.0112,180.01,120, "conversation"},
		-- Pilot trainer very last roomn in the right behind the bar
		{"da_la_socuna",60,-29.7168,-0.519991,7.77728,54.7476,121, "conversation"},
		-- npc placement test
		{"entertainer",60,-26.7168,-0.519991,7.77728,-1,119, "conversation"},

		--Hotel
		{"bartender",60,20.2,1.6,12.3,-180,1717470, "conversation"},

		--Gazebo
		{"v3_fx", 60, 4764.2, 6.1, -4795.2, 133, 0, "neutral"},
		{"kiizete", 60, 4766.36, 6.1, -4795.8, 172, 0, "neutral"},

		--Guild Hall 4923 -4783
		{"trainer_artisan",0,-0.0177415,1.13306,-13.3088,0,1717546, ""},

		--Guild Hall 4721 -4966
		{"trainer_brawler",0,-11.0386,1.13306,-13.0273,0,1717535, ""},
		{"trainer_marksman",0,0,1.13306,-13,0,1717534, ""},
		{"trainer_scout",0,-11.303,1.13306,4.63738,199,1717532, ""},

		--Guild Hall 4805 -4980
		{"trainer_architect",0,11,1.133,-14.5,0,1717555, ""},
		{"trainer_armorsmith",0,-15,1.113,0,88,1717554, ""},
		{"trainer_droidengineer",0,-11.5102,1.13306,-13.7835,2,1717557, ""},
		{"trainer_merchant",0,12,1.13306,6,180,1717553, ""},
		{"trainer_weaponsmith",0,-2.5,1.13306,-8.4,91,1717556, ""},

		--Med Center
		{"trainer_combatmedic",0,27.0188,0.26,5.47931,82,1717502, ""},
		{"trainer_combatmedic",0,-16.404,0.26,10.6808,172,1717506, ""},
		{"trainer_doctor",0,19.6344,0.26,-4.81265,37,1717502, ""},
		{"trainer_doctor",0,-25,0.26,-4,180,1717506, ""},
		{"trainer_medic",0,-17.2255,0.26,-1.2311,150,1717506, ""},
		{"trainer_medic",0,16.6671,0.26,5.91467,177,1717502, ""}
	}
}

registerScreenPlay("NabooMoeniaScreenPlay", true)

function NabooMoeniaScreenPlay:start()
	if (isZoneEnabled(self.planet)) then
		self:spawnMobiles()
		self:spawnPatrolMobiles()
		self:spawnStationaryMobiles()
		self:spawnSceneObjects()
		self:spawnGcwMobiles()
	end
end

function NabooMoeniaScreenPlay:spawnSceneObjects()
	--outside starport
	spawnSceneObject(self.planet, "object/tangible/crafting/station/public_space_station.iff", 4805.93, 4.17, -4685.56, 0, math.rad(125) )
	spawnSceneObject(self.planet, "object/tangible/crafting/station/public_space_station.iff", 4789.74, 4.17, -4709.03, 0, math.rad(125) )
end

function NabooMoeniaScreenPlay:spawnMobiles()
	local mobiles = self.mobiles

	for i = 1, #mobiles, 1 do
		local mob = mobiles[i]

		-- {template, respawn, x, z, y, direction, cell, mood}
		local pMobile = spawnMobile(self.planet, mob[1], mob[2], mob[3], mob[4], mob[5], mob[6], mob[7])

		if (pMobile ~= nil) then
			if mob[8] ~= "" then
				CreatureObject(pMobile):setMoodString(mob[8])
			end

			AiAgent(pMobile):addObjectFlag(AI_STATIC)

			if CreatureObject(pMobile):getPvpStatusBitmask() == 0 then
				CreatureObject(pMobile):clearOptionBit(AIENABLED)
			end
		end
	end

	--Outside
	spawnMobile(self.planet, "mummer_thug", 300, getRandomNumber(10) + 4856.8, 4.2, getRandomNumber(10) + -4701.5, getRandomNumber(360), 0)
	spawnMobile(self.planet, "mummer_thug", 300, getRandomNumber(10) + 4856.8, 4.2, getRandomNumber(10) + -4701.5, getRandomNumber(360), 0)
	spawnMobile(self.planet, "mummer_punk", 300, getRandomNumber(10) + 4856.8, 4.2, getRandomNumber(10) + -4701.5, getRandomNumber(360), 0)
	spawnMobile(self.planet, "mummer_punk", 300, getRandomNumber(10) + 4856.8, 4.2, getRandomNumber(10) + -4701.5, getRandomNumber(360), 0)

	--newb grind starter spawns
	--[[spawnMobile(self.planet, "diseased_nuna", 300, getRandomNumber(10) + 4599.2, 5.0, getRandomNumber(10) + -4806.4, getRandomNumber(360), 0)
	spawnMobile(self.planet, "diseased_nuna", 300, getRandomNumber(10) + 4599.2, 5.0, getRandomNumber(10) + -4806.4, getRandomNumber(360), 0)
	spawnMobile(self.planet, "diseased_nuna", 300, getRandomNumber(10) + 4599.2, 5.0, getRandomNumber(10) + -4806.4, getRandomNumber(360), 0)
	spawnMobile(self.planet, "gungan_hermit", 300, getRandomNumber(10) + 4782, 4.2, getRandomNumber(10) + -4526, getRandomNumber(360), 0)
	spawnMobile(self.planet, "gungan_hermit", 300, getRandomNumber(10) + 4782, 4.2, getRandomNumber(10) + -4526, getRandomNumber(360), 0)
	spawnMobile(self.planet, "gungan_hermit", 300, getRandomNumber(10) + 4782, 4.2, getRandomNumber(10) + -4526, getRandomNumber(360), 0)
	spawnMobile(self.planet, "gungan_hermit", 300, getRandomNumber(10) + 4782, 4.2, getRandomNumber(10) + -4526, getRandomNumber(360), 0)
	spawnMobile(self.planet, "hermit_spider", 300, getRandomNumber(10) + 4635, 5.4, getRandomNumber(10) + -4542, getRandomNumber(360), 0)
	spawnMobile(self.planet, "hermit_spider", 300, getRandomNumber(10) + 4635, 5.4, getRandomNumber(10) + -4542, getRandomNumber(360), 0)
	spawnMobile(self.planet, "hermit_spider", 300, getRandomNumber(10) + 4635, 5.4, getRandomNumber(10) + -4542, getRandomNumber(360), 0)
	spawnMobile(self.planet, "hermit_spider", 300, getRandomNumber(10) + 4635, 5.4, getRandomNumber(10) + -4542, getRandomNumber(360), 0)
	spawnMobile(self.planet, "hermit_spider", 300, getRandomNumber(10) + 4635, 5.4, getRandomNumber(10) + -4542, getRandomNumber(360), 0)
	spawnMobile(self.planet, "mott", 300, getRandomNumber(10) + 4577, 6.5, getRandomNumber(10) + -4622, getRandomNumber(360), 0)
	spawnMobile(self.planet, "mott", 300, getRandomNumber(10) + 4577, 6.5, getRandomNumber(10) + -4622, getRandomNumber(360), 0)
	spawnMobile(self.planet, "mott", 300, getRandomNumber(10) + 4577, 6.5, getRandomNumber(10) + -4622, getRandomNumber(360), 0)
	spawnMobile(self.planet, "mott", 300, getRandomNumber(10) + 4577, 6.5, getRandomNumber(10) + -4622, getRandomNumber(360), 0)
	spawnMobile(self.planet, "mott", 300, getRandomNumber(10) + 4577, 6.5, getRandomNumber(10) + -4622, getRandomNumber(360), 0)
	spawnMobile(self.planet, "mummer_thug", 300, getRandomNumber(10) + 4681, 4.0, getRandomNumber(10) + -4730, getRandomNumber(360), 0)
	spawnMobile(self.planet, "mummer_thug", 300, getRandomNumber(10) + 4681, 4.0, getRandomNumber(10) + -4730, getRandomNumber(360), 0)
	spawnMobile(self.planet, "mummer_thug", 300, getRandomNumber(10) + 4681, 4.0, getRandomNumber(10) + -4730, getRandomNumber(360), 0)]]
end

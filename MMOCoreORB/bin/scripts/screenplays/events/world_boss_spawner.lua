local ObjectManager = require("managers.object.object_manager")

WorldBossSpawner = ScreenPlay:new {
	numberOfActs = 1,
	bossesToSpawn = 1,
	initSpawnTimer = 120, -- 3600
	numReferencePoints = 29,
	secondsToDespawn = 7200, 
	notificationTime = 60,
	secondsToRespawn = 120, -- 14400
	maxRadius = 5,
	randomVariance = 5,


	bossMobileTemplates =  {
		{template = "acklay_boss", name = "Corrupted Acklay"}, 
		{template = "rancor_boss", name = "Corrupted Rancor"},
		{template = "tusken_raider_boss", name = "Corrupted Tusken Raider King"},
		{template = "droideka_boss", name = "M1r.d3r Experimental Attack Droid"},
		{template = "jawa_boss", name = "Glob the Footpad"},
	},

	screenplayName = "WorldBossSpawner",

	bossSpawnPoint = { 
		{planetName = "tatooine", xPos = -3045, yPos = 2136},
		--[[
		{planetName = "corellia", xPos = -3646, yPos = 2870},
		{planetName = "corellia", xPos = 4630, yPos = -5740},
		{planetName = "corellia", xPos = 1414, yPos = -316},
		{planetName = "naboo", xPos = -1969, yPos = 5295},
		{planetName = "naboo", xPos = -4627, yPos = 4207},
		{planetName = "naboo", xPos = -5832, yPos = -94},
		{planetName = "naboo", xPos = 2850, yPos = 1084},
		{planetName = "tatooine", xPos = -4512, yPos = -2270},
		{planetName = "tatooine", xPos = -3933, yPos = -4423},
		{planetName = "tatooine", xPos = -2575, yPos = -5517},
		{planetName = "tatooine", xPos = -4000, yPos = 6250},
		{planetName = "tatooine", xPos = -4632, yPos = -4346},
		{planetName = "lok", xPos = 4578, yPos = -1151},
		{planetName = "lok", xPos = -70, yPos = 2650},
		{planetName = "dantooine", xPos = 4195, yPos = 5208},	
		{planetName = "dantooine", xPos = -3819, yPos = -5726},
		{planetName = "dantooine", xPos = -555, yPos = -3825},
		{planetName = "dathomir", xPos = -4002, yPos = -58},		
		{planetName = "dathomir", xPos = -2102, yPos = 3165},
		{planetName = "dathomir", xPos = 5676, yPos = 1901},	
		{planetName = "endor", xPos = -4550, yPos = -2250},
		{planetName = "endor", xPos = -1714, yPos = 9},	
		{planetName = "rori", xPos = -2073, yPos = 3339},
		{planetName = "rori", xPos = 772, yPos = -2109},
		{planetName = "talus", xPos = -2595, yPos =  3724},
		{planetName = "talus", xPos = 4285, yPos = 1032},
		{planetName = "yavin4", xPos = 5097, yPos = 5537},
		{planetName = "yavin4", xPos = 466, yPos = -693},
		{planetName = "yavin4", xPos = -3150, yPos = -3050},]]--
	},
	
	bigGameHunterSpawns = {
		{"corellia", "big_game_hunter", 0, -128.21, 28, -4758.9, 282, 0},
		{"naboo", "big_game_hunter", 0, -4876.47, 6.42773, 4190.98, 177, 0},
		{"tatooine", "big_game_hunter", 0, 3517.26, 5, -4799.64, 144, 0},
		{"lok", "big_game_hunter", 0, 438.818, 8.72217, 5505.23, 103, 0},
		{"dantooine", "big_game_hunter", 0, -657.838, 3, 2472.76, 60, 0},
		{"dathomir", "big_game_hunter", 0, 595.538, 6, 3106.55, 236, 0},
		{"endor", "big_game_hunter", 0, 3228.4, 24, -3500.69, 43, 0},
		{"rori", "big_game_hunter", 0, -5302.11, 80.0358, -2197.98, 102, 0},
		{"talus", "big_game_hunter", 0, 320.404, 6, -2908.43, 61, 0},
		{"yavin4", "big_game_hunter", 0, -6928.55, 73, -5686.36, 183, 0},
	}
}

registerScreenPlay("WorldBossSpawner", true)

function WorldBossSpawner:start()
	self:pickBossSpawn()
	local pBoss
	createEvent((self.initSpawnTimer - self.notificationTime) * 1000, "WorldBossSpawner", "notifyBossSpawning", pBoss, "")
	createEvent(self.initSpawnTimer * 1000, "WorldBossSpawner", "spawnMobiles", pBoss, "")
end

function WorldBossSpawner:spawnMobiles()
	local spawns = 1
	local pBoss

	while (spawns < self.bossesToSpawn + 1) do
		self:respawnBoss(pBoss)		
		spawns = spawns + 1
	end
end

function WorldBossSpawner:setupBoss(pBoss)
	createObserver(OBJECTDESTRUCTION, "WorldBossSpawner", "notifyBossDead", pBoss)
	createEvent(getRandomNumber(self.secondsToDespawn - self.randomVariance, self.secondsToDespawn + self.randomVariance) * 1000, "WorldBossSpawner", "despawnBoss", pBoss, "")
end

function WorldBossSpawner:notifyBossDead(pBoss, pKiller)
	if (pBoss == nil) then
		return 1
	end

	if (pKiller == nil) then
		return 1
	end

	local returnTime = getRandomNumber(self.secondsToRespawn - self.randomVariance, self.secondsToRespawn + self.randomVariance)
	createEvent((returnTime - self.notificationTime) * 1000, "WorldBossSpawner", "notifyBossSpawning" , pBoss, "")
	createEvent(returnTime * 1000, "WorldBossSpawner", "respawnBoss", pBoss, "")
	print("Boss was killed, initiating respawn.")
	local bossName = self:getBossName(pBoss)
	local zone = self:getBossZone(pBoss)

	if (bossName ~= nil and zone ~= nil) then
		CreatureObject(pBoss):broadcastToServer("\\#6699ff <Incomming Transmission> \n\\#ffff99" .. bossName .. " \\#ff9966 has been slain on " .. zone)
		CreatureObject(pBoss):broadcastToDiscord("\\#6699ff <Incomming Transmission> \n\\#ffff99" .. bossName .. " \\#ff9966 has been slain on " .. zone) 
		deleteStringData(SceneObject(pBoss):getObjectID() .. ":name")
		deleteStringData(SceneObject(pBoss):getObjectID() .. ":zone")
		deleteData("worldBosses:spawnIndex")
		deleteData("worldBosses:templateIndex")
		for i = 1, self.bossesToSpawn, 1 do
			local checkBossPlanetData = readData(zone .. ":" .. i)
			if (checkBossPlanetData ~= nil and checkBossPlanetData == SceneObject(pBoss):getObjectID()) then
				deleteData(zone .. ":" .. i)
				break
			end
		end
	end

	return 1
end


function WorldBossSpawner:pickBossSpawn()

	local spawnIndex = getRandomNumber(1, #self.bossSpawnPoint)
	local templateIndex = getRandomNumber(1, #self.bossMobileTemplates)
	writeData("worldBosses:spawnIndex", spawnIndex)
	writeData("worldBosses:templateIndex", templateIndex)
	

end


function WorldBossSpawner:notifyBossSpawning(pBoss)

	self:pickBossSpawn()

	local spawnIndex = tonumber(readData("worldBosses:spawnIndex"))
	local templateIndex = tonumber(readData("worldBosses:templateIndex"))

	local bossObject = self.bossMobileTemplates[templateIndex]
	local bossName = bossObject.name
	local zone = self.bossSpawnPoint[spawnIndex].planetName

	local xPos = self.bossSpawnPoint[spawnIndex].xPos
	local yPos = self.bossSpawnPoint[spawnIndex].yPos

	if (pBoss ~= nil and bossName ~= nil and zone ~= nil and xPos ~= nil and yPos ~= nil) then
		CreatureObject(pBoss):broadcastToServer("\\#6699ff <Incoming Transmission>\n".."Rumors are spreading of a \\#ffff99" .. bossName .. " \\#66ff99appearing on " .. zone .. "\nCoordinates: " .. math.floor(xPos) .. ", " .. math.floor(yPos)) 
		CreatureObject(pBoss):broadcastToDiscord("\\#6699ff <Incoming Transmission>\n".."Rumors are spreading of a \\#ffff99" .. bossName .. " \\#66ff99appearing on " .. zone .. "\nCoordinates: " .. math.floor(xPos) .. ", " .. math.floor(yPos))
	end

	return 1
end

function WorldBossSpawner:respawnBoss(pOldBoss)


	local spawnIndex = tonumber(readData("worldBosses:spawnIndex"))
	local templateIndex = tonumber(readData("worldBosses:templateIndex"))

	local bossObject = self.bossMobileTemplates[templateIndex]
	local bossTemplate = bossObject.template
	local referencePoint = spawnIndex
	local zone = self.bossSpawnPoint[referencePoint].planetName
		
	if (not isZoneEnabled(zone)) then
		
		local counter = 1
			
		while (not isZoneEnabled(zone) and counter <= 11) do
			referencePoint = getRandomNumber(1, #self.bossSpawnPoint)
			zone = self.bossSpawnPoint[referencePoint].planetName
				
			if (counter == 11) then
				return
			end
				
			counter = counter + 1
		end
	end

	local xPos = self.bossSpawnPoint[referencePoint].xPos
	local yPos = self.bossSpawnPoint[referencePoint].yPos
	local pSpawner = spawnSceneObject(zone, "object/tangible/spawning/quest_spawner.iff", xPos, 0, yPos, 0, 0)

	if (pSpawner == nil) then
		return
	end

	local spawnPoint = getSpawnPoint(zone, xPos, yPos, self.minimumDistance, self.maxRadius, true)
		
	if (spawnPoint == nil) then
			spawnPoint = { spawnerX, getTerrainHeight(pSpawner, xPos, yPos), yPos }
	end

	local pBoss = spawnMobile(zone, bossTemplate, 0, spawnPoint[1], spawnPoint[2], spawnPoint[3], getRandomNumber(360) - 180, 0)
	SceneObject(pSpawner):destroyObjectFromWorld()	

		if (pBoss ~= nil) then
			local mechanicType = ""

			if (bossTemplate == "deathsting_boss") then
				mechanicType = "poisonGasCloudMechanic"
			elseif (bossTemplate == "wampa_boss" or bossTemplate == "kkorrwrot_boss") then
				mechanicType = "coldFieldMechanic"
			end
			
			if (mechanicType ~= "") then
				createObserver(STARTCOMBAT, mechanicType, "setupMech", pBoss, "")
			end

			createEvent(30, "WorldBossSpawner", "setupBoss", pBoss, "")

			--self:spawnBigGameHunter(pBoss, zone)

			print("World Boss: " .. bossObject.name .. " spawned at " .. spawnPoint[1] .. ", " .. spawnPoint[3] .. ", " .. zone)

			writeStringData(SceneObject(pBoss):getObjectID() .. ":name", bossObject.name)
			writeStringData(SceneObject(pBoss):getObjectID() .. ":zone", zone)

			for i = 1, self.bossesToSpawn, 1 do
				if (readData(zone .. ":" .. i) == nil or readData(zone .. ":" .. i) == 0) then
					writeData(zone .. ":" .. i, SceneObject(pBoss):getObjectID())
					break
				end
			end

			CreatureObject(pBoss):broadcastToServer("\\#6699ff <Incoming Transmission>\n".."a \\#ffff99" .. bossObject.name .. " \\#66ff99has been sighted on " .. zone .. "\nCoordinates: " .. math.floor(spawnPoint[1]) .. ", " .. math.floor(spawnPoint[3])) 
			CreatureObject(pBoss):broadcastToDiscord("\\#6699ff <Incoming Transmission>\n".."a \\#ffff99" .. bossObject.name .. " \\#66ff99has been sighted on " .. zone .. "\nCoordinates: " .. math.floor(spawnPoint[1]) .. ", " .. math.floor(spawnPoint[3]))
		end

end

function WorldBossSpawner:despawnBoss(pBoss)
	if (pBoss == nil) then
		return
	end

	if (CreatureObject(pBoss):isDead()) then
		local bossZone = readStringData(SceneObject(pBoss):getObjectID() .. ":zone")
		deleteStringData(SceneObject(pBoss):getObjectID() .. ":name")
		deleteStringData(SceneObject(pBoss):getObjectID() .. ":zone")
		deleteData("worldBosses:spawnIndex")
		deleteData("worldBosses:templateIndex")

		for i = 1, self.bossesToSpawn, 1 do
			local checkBossPlanetData = readData(bossZone .. ":" .. i)
			if (checkBossPlanetData ~= nil and checkBossPlanetData == SceneObject(pBoss):getObjectID()) then
				deleteData(bossZone .. ":" .. i)
				break
			end
		end
		return
	end

	if (CreatureObject(pBoss):isInCombat()) then
		createEvent(getRandomNumber(self.secondsToDespawn - self.randomVariance, self.secondsToDespawn + self.randomVariance) * 1000, "WorldBossSpawner", "despawnBoss", pBoss, "")
		return		
	end

	print("Boss was not killed, initiating despawn/respawn.")
	
	local bossName = self:getBossName(pBoss)
	local zone = self:getBossZone(pBoss)

	if (bossName ~= nil and zone ~= nil) then
		CreatureObject(pBoss):broadcastToServer("\\#6699ff <Incoming Transmission> \n\n \\#ffff99" .. bossName .. " \\#ffccff has gone back into hiding on " .. zone) 
		CreatureObject(pBoss):broadcastToDiscord("\\#6699ff <Incoming Transmission> \n\n \\#ffff99" .. bossName .. " \\#ffccff has gone back into hiding on " .. zone)
	end

	for i = 1, self.bossesToSpawn, 1 do
		local checkBossPlanetData = readData(zone .. ":" .. i)
		if (checkBossPlanetData ~= nil and checkBossPlanetData == SceneObject(pBoss):getObjectID()) then
			deleteData(zone .. ":" .. i)
			break
		end
	end
	SceneObject(pBoss):destroyObjectFromWorld()
	deleteStringData(SceneObject(pBoss):getObjectID() .. ":name")
	deleteStringData(SceneObject(pBoss):getObjectID() .. ":zone")
	deleteData("worldBosses:spawnIndex")
	deleteData("worldBosses:templateIndex")
	local returnTime = getRandomNumber(self.secondsToRespawn - self.randomVariance, self.secondsToRespawn + self.randomVariance)
	createEvent((returnTime - self.notificationTime) * 1000, "WorldBossSpawner", "notifyBossSpawning", pBoss, "")
	createEvent(returnTime * 1000, "WorldBossSpawner", "respawnBoss", pNewBoss, "")
	return 1
end

function WorldBossSpawner:getBossName(pBoss)
	local bossName = readStringData(SceneObject(pBoss):getObjectID() .. ":name")
	return bossName
end

function WorldBossSpawner:getBossZone(pBoss)
	local bossZone = readStringData(SceneObject(pBoss):getObjectID() .. ":zone")
	return bossZone
end

function WorldBossSpawner:spawnBigGameHunter(pBoss, planet)
	if (pBoss ~= nil or CreatureObject(pBoss):isDead() == false) then
		for i = 1, #self.bigGameHunterSpawns, 1 do
			local bghSpawn = self.bigGameHunterSpawns[i]
			if (bghSpawn[1] == planet) then

				if (readData(planet .. ":bghPlanet") == 0) then
					local pBGH = spawnMobile(bghSpawn[1], bghSpawn[2], bghSpawn[3], bghSpawn[4], bghSpawn[5], bghSpawn[6], bghSpawn[7], bghSpawn[8])
					if (pBGH ~= nil) then
						writeData(planet .. ":bghPlanet", SceneObject(pBGH):getObjectID())
						writeStringData(SceneObject(pBGH):getObjectID() .. ":bghPlanet", planet)
						createEvent(60 * 1000, "WorldBossSpawner", "despawnBigGameHunter", pBGH, "")
					end
				end
			end
		end
	end
end

function WorldBossSpawner:despawnBigGameHunter(pBGH)
	if (pBGH ~= nil) then
		local BGHPlanet = readStringData(SceneObject(pBGH):getObjectID() .. ":bghPlanet")

		for i = 1, self.bossesToSpawn, 1 do
			local checkBossPlanetData = readData(BGHPlanet .. ":" .. i)
			if (checkBossPlanetData ~= nil and checkBossPlanetData ~= 0) then
				createEvent(30 * 1000, "WorldBossSpawner", "despawnBigGameHunter", pBGH, "")
				return
			end
		end
		deleteData(BGHPlanet .. ":bghPlanet")
		deleteStringData(SceneObject(pBGH):getObjectID() .. ":bghPlanet")
		SceneObject(pBGH):destroyObjectFromWorld()
	end
end

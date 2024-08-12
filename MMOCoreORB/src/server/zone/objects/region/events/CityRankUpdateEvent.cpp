#include "server/zone/objects/region/CityRegion.h"
#include "CityRankUpdateEvent.h"
#include "server/zone/managers/city/CityManager.h"
#include "server/zone/ZoneServer.h"

CityRankUpdateEvent::CityRankUpdateEvent(CityRegion* city, ZoneServer* zserv) : Task() {
	cityRegion = city;
	zoneServer = zserv;

	setCustomTaskQueue("slowQueue");
}

void CityRankUpdateEvent::run() {
	if (zoneServer == nullptr || zoneServer->isServerShuttingDown()) return;

	ManagedReference<CityRegion*> city = cityRegion.get();
	if (city == nullptr) return;

	Locker locker(city);
	if (zoneServer->isServerLoading()) {
		city->rescheduleRankUpdateEvent(0);
		return;
	}

	CityManager* cityManager = zoneServer->getCityManager();
	cityManager->processCityRankUpdate(city);
}

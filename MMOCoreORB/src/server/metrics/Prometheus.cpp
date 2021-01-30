#include "Prometheus.h"

#include <iostream>
#include <prometheus/exposer.h>
#include <prometheus/registry.h>

Prometheus* Prometheus::mSingleton = new (std::nothrow) Prometheus;

Prometheus::Prometheus() {
	mExposer = new prometheus::Exposer{"127.0.0.1:9323"};

	mRegistry = std::make_shared<prometheus::Registry>();

	Counters = new VectorMap<String, prometheus::Counter*>();
	Counters->put("logins", &prometheus::BuildCounter().Name("swgemu_login_total").Register(*mRegistry).Add({}));
	
	Gauges = new VectorMap<String, prometheus::Gauge*>();
	Gauges->put("server_uptime", &prometheus::BuildGauge().Name("swgemu_server_uptime").Register(*mRegistry).Add({}));
	Gauges->put("account_online", &prometheus::BuildGauge().Name("swgemu_account_online").Register(*mRegistry).Add({}));
	Gauges->put("player_online", &prometheus::BuildGauge().Name("swgemu_player_online").Register(*mRegistry).Add({}));
	Gauges->put("player_afk", &prometheus::BuildGauge().Name("swgemu_player_afk").Register(*mRegistry).Add({}));

	// Zones
	auto &zone_guage = prometheus::BuildGauge().Name("swgemu_player_zone").Register(*mRegistry);
	Gauges->put("player_zone_corellia", &zone_guage.Add({{"name", "corellia"}}));
	Gauges->put("player_zone_dantooine", &zone_guage.Add({{"name", "dantooine"}}));
	Gauges->put("player_zone_dathomir", &zone_guage.Add({{"name", "dathomir"}}));
	Gauges->put("player_zone_dungeon1", &zone_guage.Add({{"name", "dungeon1"}}));
	Gauges->put("player_zone_endor", &zone_guage.Add({{"name", "endor"}}));
	Gauges->put("player_zone_lok", &zone_guage.Add({{"name", "lok"}}));
	Gauges->put("player_zone_naboo", &zone_guage.Add({{"name", "naboo"}}));
	Gauges->put("player_zone_rori", &zone_guage.Add({{"name", "rori"}}));
	Gauges->put("player_zone_talus", &zone_guage.Add({{"name", "talus"}}));
	Gauges->put("player_zone_tatooine", &zone_guage.Add({{"name", "tatooine"}}));
	Gauges->put("player_zone_tutorial", &zone_guage.Add({{"name", "tutorial"}}));
	Gauges->put("player_zone_yavin4", &zone_guage.Add({{"name", "yavin4"}}));

	mExposer->RegisterCollectable(mRegistry);
}

void Prometheus::CounterIncrement(String name){
	auto counter = Counters->get(name);
	if( counter == nullptr ){
		std::cout << "Invalid Counter " << name.toCharArray() << std::endl;
	}
	counter->Increment();
}

void Prometheus::GaugeIncrement(String name){
	auto gauge = Gauges->get(name);
	if( gauge == nullptr ){
		std::cout << "Invalid Gauge " << name.toCharArray() << std::endl;
	}
	gauge->Increment();
}

void Prometheus::GaugeSet(String name, double value){
	auto gauge = Gauges->get(name);
	if( gauge == nullptr ){
		std::cout << "Invalid Gauge " << name.toCharArray() << std::endl;
	}
	gauge->Set(value);
}

void Prometheus::ResetZones(){
	GaugeSet("player_zone_corellia", 0);
	GaugeSet("player_zone_dantooine", 0);
	GaugeSet("player_zone_dathomir", 0);
	GaugeSet("player_zone_dungeon1", 0);
	GaugeSet("player_zone_endor", 0);
	GaugeSet("player_zone_lok", 0);
	GaugeSet("player_zone_naboo", 0);
	GaugeSet("player_zone_rori", 0);
	GaugeSet("player_zone_talus", 0);
	GaugeSet("player_zone_tatooine", 0);
	GaugeSet("player_zone_tutorial", 0);
	GaugeSet("player_zone_yavin4", 0);
}

Prometheus* Prometheus::GetInstance(){
	return mSingleton;
}

Prometheus::~Prometheus(){

}

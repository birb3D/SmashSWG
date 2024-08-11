#include "Prometheus.h"

#include <iostream>
#include <prometheus/exposer.h>
#include <prometheus/registry.h>

Prometheus* Prometheus::mSingleton = new (std::nothrow) Prometheus;

String *Professions;

Prometheus::Prometheus() {
	mExposer = new prometheus::Exposer{"0.0.0.0:9323"};

	mRegistry = std::make_shared<prometheus::Registry>();

	Counters = new VectorMap<String, prometheus::Counter*>();
	Counters->put("logins", &prometheus::BuildCounter().Name("swgemu_login_total").Register(*mRegistry).Add({}));
	
	Gauges = new VectorMap<String, prometheus::Gauge*>();
	Gauges->put("server_uptime", &prometheus::BuildGauge().Name("swgemu_server_uptime").Register(*mRegistry).Add({}));
	Gauges->put("account_online", &prometheus::BuildGauge().Name("swgemu_account_online").Register(*mRegistry).Add({}));
	Gauges->put("player_online", &prometheus::BuildGauge().Name("swgemu_player_online").Register(*mRegistry).Add({}));
	Gauges->put("player_afk", &prometheus::BuildGauge().Name("swgemu_player_afk").Register(*mRegistry).Add({}));
	Gauges->put("lots_used", &prometheus::BuildGauge().Name("swgemu_lots_used").Register(*mRegistry).Add({}));

	// Factions
	auto &faction_gauge = prometheus::BuildGauge().Name("swgemu_player_faction").Register(*mRegistry);
	Gauges->put("player_faction_neutral", &faction_gauge.Add({{"name", "neutral"}}));
	Gauges->put("player_faction_rebel", &faction_gauge.Add({{"name", "rebel"}}));
	Gauges->put("player_faction_imperial", &faction_gauge.Add({{"name", "imperial"}}));

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

	// professions
	Professions = new String[33]{
	    "artisan", "brawler", "entertainer", "marksman", "medic", "politician", "scout",
		"1hsword", "2hsword", "architect", "armorsmith", "bio_engineer", "bountyhunter",
	    "carbine", "chef", "combatmedic", "commando", "creaturehandler", "dancer", "doctor",
	    "droidengineer", "imagedesigner", "merchant", "musician", "pistol", "polearm",
	    "ranger", "rifleman", "smuggler", "squadleader", "tailor", "unarmed", "weaponsmith"
	};

	auto &profession_guage = prometheus::BuildGauge().Name("swgemu_player_profession").Register(*mRegistry);
	for( int i = 0; i < 33; i++){
		Gauges->put("player_profession_" + Professions[i] + "_novice", &profession_guage.Add({{"rank", "novice"}, {"name", Professions[i]}}));
		Gauges->put("player_profession_" + Professions[i] + "_master", &profession_guage.Add({{"rank", "master"}, {"name", Professions[i]}}));
	}

	// Guilds
	Guilds = &prometheus::BuildGauge().Name("swgemu_guild_players").Register(*mRegistry);

	mExposer->RegisterCollectable(mRegistry);
}

void Prometheus::CounterIncrement(String name){
	auto counter = Counters->get(name);
	if( counter == nullptr ){
		std::cout << "Invalid Counter " << name.toCharArray() << std::endl;
		return;
	}
	counter->Increment();
}

void Prometheus::GaugeIncrement(String name){
	auto gauge = Gauges->get(name);
	if( gauge == nullptr ){
		std::cout << "Invalid Gauge " << name.toCharArray() << std::endl;
		return;
	}
	gauge->Increment();
}

void Prometheus::GaugeAdd(String name, double value){
	auto gauge = Gauges->get(name);
	if( gauge == nullptr ){
		std::cout << "Invalid Gauge " << name.toCharArray() << std::endl;
		return;
	}
	gauge->Set(gauge->Value() + value);
}

void Prometheus::GaugeSet(String name, double value){
	auto gauge = Gauges->get(name);
	if( gauge == nullptr ){
		std::cout << "Invalid Gauge " << name.toCharArray() << std::endl;
		return;
	}
	gauge->Set(value);
}

void Prometheus::GuildIncrement(String name, String abbr){
	if(!Gauges->contains("guild_players_" + abbr) ) {
		Gauges->put("guild_players_" + abbr, &Guilds->Add({{"name", name}, {"abbreviation", abbr}}));
	}

	auto gauge = Gauges->get("guild_players_" + abbr);
	if( gauge == nullptr ){
		std::cout << "Invalid Gauge guild_" << abbr.toCharArray() << std::endl;
		return;
	}
	gauge->Increment();
}

void Prometheus::ResetZones(){
	for (auto i = Gauges->begin(); i != Gauges->end(); ++i){
		if( (*i).getKey().contains("player_zone_") ) (*i).getValue()->Set(0);
	}
}

void Prometheus::ResetProfessions(){
	for (auto i = Gauges->begin(); i != Gauges->end(); ++i){
		if( (*i).getKey().contains("player_profession_") ) (*i).getValue()->Set(0);
	}
}

void Prometheus::ResetGuilds(){
	for (auto i = Gauges->begin(); i != Gauges->end(); ++i){
		if( (*i).getKey().contains("guild_") ) (*i).getValue()->Set(0);
	}
}

Prometheus* Prometheus::GetInstance(){
	return mSingleton;
}

Prometheus::~Prometheus(){

}

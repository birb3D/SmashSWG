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
    Gauges->put("player_online", &prometheus::BuildGauge().Name("swgemu_player_online").Register(*mRegistry).Add({}));
    Gauges->put("player_afk", &prometheus::BuildGauge().Name("swgemu_player_afk").Register(*mRegistry).Add({}));

    mExposer->RegisterCollectable(mRegistry);
}

prometheus::Counter& Prometheus::GetCounter(String name) {
  std::cout << name.toCharArray() << " " << Counters << " " << Counters->contains(name) << " " << Counters->get(name) << std::endl;
  return *Counters->get(name);
}

prometheus::Gauge& Prometheus::GetGauge(String name) {
  std::cout << name.toCharArray() << " " << Gauges << " " << Gauges->contains(name) << " " << Gauges->get(name) << std::endl;  
  return *Gauges->get(name);
}

Prometheus* Prometheus::GetInstance(){
    return mSingleton;
}

Prometheus::~Prometheus(){

}

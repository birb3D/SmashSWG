#ifndef PROMETHEUS_H_
#define PROMETHEUS_H_

#include <prometheus/counter.h>
#include <prometheus/gauge.h>
#include <prometheus/exposer.h>
#include <prometheus/registry.h>

#include "system/util/VectorMap.h"

namespace server {
namespace metrics {
	class Prometheus {
	public:
	  prometheus::Counter& GetCounter(String name);
	  prometheus::Gauge& GetGauge(String name);	  
        static Prometheus* GetInstance();
	private:
        Prometheus();
        ~Prometheus();
        Prometheus(const Prometheus &signal);
        const Prometheus &operator=(const Prometheus &signal);

	VectorMap<String, prometheus::Counter*> *Counters;
        VectorMap<String, prometheus::Gauge*> *Gauges;

	prometheus::Exposer *mExposer;
        std::shared_ptr<prometheus::Registry> mRegistry;
        static Prometheus *mSingleton;
	};
} // namespace metrics
} // namespace server

using namespace server::metrics;

#endif // PROMETHEUS_H_


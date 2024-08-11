#ifndef PROMETHEUS_H_
#define PROMETHEUS_H_

#include <prometheus/counter.h>
#include <prometheus/gauge.h>
#include <prometheus/exposer.h>
#include <prometheus/registry.h>
#include <prometheus/family.h>

#include "system/util/VectorMap.h"

namespace server {
namespace metrics {
	class Prometheus {
		public:
			void CounterIncrement(String name);
			void GaugeIncrement(String name);
			void GaugeAdd(String name, double value);
			void GaugeSet(String name, double value);
			void GuildIncrement(String name, String abbr);
			void ResetZones();
			void ResetGuilds();
			void ResetProfessions();
			static Prometheus* GetInstance();
		private:
			Prometheus();
			~Prometheus();
			Prometheus(const Prometheus &signal);
			const Prometheus &operator=(const Prometheus &signal);

			VectorMap<String, prometheus::Counter*> *Counters;
			VectorMap<String, prometheus::Gauge*> *Gauges;
			prometheus::Family<prometheus::Gauge> *Guilds;

			prometheus::Exposer *mExposer;
			std::shared_ptr<prometheus::Registry> mRegistry;
			static Prometheus *mSingleton;
	};
} // namespace metrics
} // namespace server

using namespace server::metrics;

#endif // PROMETHEUS_H_


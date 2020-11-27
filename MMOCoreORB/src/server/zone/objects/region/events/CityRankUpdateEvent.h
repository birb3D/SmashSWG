#ifndef CITYRANKUPDATEEVENT_H_
#define CITYRANKUPDATEEVENT_H_

#include "engine/engine.h"

namespace server {
    namespace zone {
        class ZoneServer;

        namespace objects {
            namespace region {
                class CityRegion;
            }
        }
    }
}

using namespace server::zone;
using namespace server::zone::objects::region;

namespace server {
    namespace zone {
        namespace objects {
            namespace region {
                namespace events {
                    class CityRankUpdateEvent : public Task {
                        ManagedReference<ZoneServer*> zoneServer;
                        ManagedWeakReference<CityRegion*> cityRegion;

                        public:
                            CityRankUpdateEvent(CityRegion* city, ZoneServer* zserv);
                            void run();
                    };
                }
            }
        }
    }
}

using namespace server::zone::objects::region::events;

#endif /* CITYRANKUPDATEEVENT_H_ */

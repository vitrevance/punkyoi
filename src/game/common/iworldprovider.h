#ifndef P_IWORLDPROVIDER
#define P_IWORLDPROVIDER

#include <game/core.h>
#include <game/common/world.h>

namespace punkyoi::common {

    class IWorldProvider {
    public:
        virtual void init() = 0;
        virtual std::shared_ptr<World> createWorld(punkyoi_api::events::EventBus&) = 0;
    };
}

#endif
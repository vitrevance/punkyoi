#ifndef P_DINOWORLDPROVIDER
#define P_DINOWORLDPROVIDER

#include <game/core.h>
#include <game/common/iworldprovider.h>
#include <game/common/world.h>
#include <game/concrete/entityplayer.h>

namespace punkyoi::concrete {

    class DinoWorldProvider : public ::punkyoi::common::IWorldProvider {
    public:
        DinoWorldProvider();
        ~DinoWorldProvider();

        virtual void init() override;
        std::shared_ptr<::punkyoi::common::World> createWorld(punkyoi_api::events::EventBus&) override;
    };
}

#endif
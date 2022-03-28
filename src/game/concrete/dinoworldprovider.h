#ifndef P_DINOWORLDPROVIDER
#define P_DINOWORLDPROVIDER

#include <game/core.h>
#include <game/common/iworldprovider.h>
#include <game/common/world.h>
#include <game/concrete/entityplayer.h>
#include <game/concrete/levelcontroller.h>
#include <game/concrete/uiscreen.h>

namespace punkyoi::concrete {

    class DinoWorldProvider : public ::punkyoi::common::IWorldProvider {
    public:
        DinoWorldProvider();
        virtual ~DinoWorldProvider();

        virtual void init() override;
        std::shared_ptr<::punkyoi::common::World> createWorld(punkyoi_api::events::EventBus&) override;
    };
}

#endif
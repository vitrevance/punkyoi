#ifndef P_SINGLETON
#define P_SINGLETON

#include <api/iassetmanager.h>
#include <api/events/eventbus.h>

namespace punkyoi {

    ::punkyoi_api::IAssetManager& getAssetManager();
    ::punkyoi_api::events::EventBus& getEventBus();
}

#endif
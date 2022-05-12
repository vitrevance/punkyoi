#ifndef P_SINGLETON
#define P_SINGLETON

#include <game/common/assetmanager.h>
#include <game/common/soundengine.h>
#include <api/events/eventbus.h>

namespace punkyoi {

    common::AssetManager& getAssetManager();
    ::punkyoi_api::events::EventBus& getEventBus();
    common::SoundEngine& getSoundEngine();
}

#endif
#include <game/core.h>

#if CURRENT_PLATFORM == PLATFORM_LINUX

#include "linux_factory.h"

namespace punkyoi::platform::linux {

    ::punkyoi_api::IWindow* LinuxFactory::createWindow(const ::punkyoi_api::WindowProps& properties, ::std::shared_ptr<::punkyoi_api::events::EventBus> eventBus) {
        return new PlatformWindow(properties, eventBus);
    };

    ::punkyoi_api::WindowProps LinuxFactory::getDefaultWindowProps() {
        return ::punkyoi_api::WindowProps{ "Punkyoi", 1280, 720, false, false };
    }

    ::punkyoi_api::IRenderer* LinuxFactory::createRenderer() {
        return new PlatformRenderer();
    }

    ::punkyoi_api::IAssetManager* LinuxFactory::createAssetManager() {
        return new PlatformAssetManager();
    }
}

#endif
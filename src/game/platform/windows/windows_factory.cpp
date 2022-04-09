#include <game/core.h>

#if CURRENT_PLATFORM == PLATFORM_WINDOWS

#include "windows_factory.h"

namespace punkyoi::platform::windows {

    ::punkyoi_api::IWindow* WindowsFactory::createWindow(const ::punkyoi_api::WindowProps& properties, ::std::shared_ptr<::punkyoi_api::events::EventBus> eventBus) {
        return new PlatformWindow(properties, eventBus);
    };

    ::punkyoi_api::WindowProps WindowsFactory::getDefaultWindowProps() {
        return ::punkyoi_api::WindowProps{ "Punkyoi", 1280, 720, false, false };
    }

    ::punkyoi_api::IRenderer* WindowsFactory::createRenderer() {
        return new PlatformRenderer();
    }

    ::punkyoi_api::IAssetManager* WindowsFactory::createAssetManager() {
        return new PlatformAssetManager();
    }
}

#endif
#pragma once

#include <game/platform/linux/window.h>

namespace punkyoi::platform {

    #define PLATFORM_LINUX 0
    #define PLATFORM_WINDOWS 1

    enum class PlatformType {
        Linux = PLATFORM_LINUX,
        Windows = PLATFORM_WINDOWS
    };

    #ifdef __linux
    static constexpr PlatformType currentPlatform = PlatformType::Linux;
    #elif defined(WIN32)
    static constexpr Platform currentPlatform = Platform::Windows;
    #endif

    class Platform {
    public:
        virtual ::punkyoi_api::IWindow* createWindow(const ::punkyoi::WindowProps& properties, ::std::shared_ptr<::punkyoi_api::events::EventBus> eventBus);
    };

    #if (currentPlatform == PLATFORM_LINUX)

    ::punkyoi_api::IWindow* Platform::createWindow(const ::punkyoi::WindowProps& properties, ::std::shared_ptr<::punkyoi_api::events::EventBus> eventBus) {
        ::punkyoi::platform::linux::LinuxWindow* result = new ::punkyoi::platform::linux::LinuxWindow(properties, eventBus);
        return dynamic_cast<::punkyoi_api::IWindow*>(result);
    }

    #endif
}
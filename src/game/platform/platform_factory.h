#ifndef P_PLATFORM_FACTORY
#define P_PLATFORM_FACTORY

#include <api/iwindow.h>
#include <api/events/eventbus.h>
#include <game/window.h>
#include <core.h>

namespace punkyoi::platform {

    class Platform {
    public:
        virtual ::punkyoi_api::IWindow* createWindow(const ::punkyoi::WindowProps& properties, ::std::shared_ptr<::punkyoi_api::events::EventBus> eventBus);
    };

    #if (CURRENT_PLATFORM == PLATFORM_LINUX)

#include <game/platform/linux/window.h>

    ::punkyoi_api::IWindow* Platform::createWindow(const ::punkyoi::WindowProps& properties, ::std::shared_ptr<::punkyoi_api::events::EventBus> eventBus) {
        ::punkyoi::platform::linux::LinuxWindow* result = new ::punkyoi::platform::linux::LinuxWindow(properties, eventBus);
        return dynamic_cast<::punkyoi_api::IWindow*>(result);
    }

    #endif
}

#endif
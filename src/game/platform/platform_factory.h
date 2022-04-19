#ifndef P_PLATFORM_FACTORY
#define P_PLATFORM_FACTORY

#include <api/iwindow.h>
#include <api/events/eventbus.h>
#include <api/iwindow.h>
#include <game/core.h>

namespace punkyoi::platform {

    class PlatformFactory {
    public:
        virtual ::punkyoi_api::IWindow* createWindow(const ::punkyoi_api::WindowProps& properties, ::std::shared_ptr<::punkyoi_api::events::EventBus> eventBus) = 0;
        virtual ::punkyoi_api::WindowProps getDefaultWindowProps() = 0;
    };
}

#endif
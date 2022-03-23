#ifndef P_PLATFORM_FACTORY
#define P_PLATFORM_FACTORY

#include <game/core.h>
#include <api/iwindow.h>
#include <api/events/eventbus.h>
#include <api/iwindow.h>
#include <api/irenderer.h>
#include <api/iassetmanager.h>

namespace punkyoi::platform {

    class PlatformFactory {
    public:
        virtual ~PlatformFactory() = default;
        virtual ::punkyoi_api::IWindow* createWindow(const ::punkyoi_api::WindowProps& properties, ::std::shared_ptr<::punkyoi_api::events::EventBus> eventBus) = 0;
        virtual ::punkyoi_api::WindowProps getDefaultWindowProps() = 0;
        virtual ::punkyoi_api::IRenderer* createRenderer() = 0;
        virtual ::punkyoi_api::IAssetManager* createAssetManager() = 0;
    };
}

#endif
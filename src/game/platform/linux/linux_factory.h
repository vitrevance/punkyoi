#ifndef P_LINUX_FACTORY
#define P_LINUX_FACTORY

#include <game/platform/platform_factory.h>
#include <game/platform/linux/window.h>
#include <game/platform/linux/renderer.h>
#include <game/platform/linux/assetmanager.h>

namespace punkyoi::platform::linux {

    class LinuxFactory : public ::punkyoi::platform::PlatformFactory {
        virtual ::punkyoi_api::IWindow* createWindow(const ::punkyoi_api::WindowProps& properties, ::std::shared_ptr<::punkyoi_api::events::EventBus> eventBus) override;
        virtual ::punkyoi_api::WindowProps getDefaultWindowProps() override;
        virtual ::punkyoi_api::IRenderer* createRenderer() override;
        virtual ::punkyoi_api::IAssetManager* createAssetManager() override;
    };
}


#endif
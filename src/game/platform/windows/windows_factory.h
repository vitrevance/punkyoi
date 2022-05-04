#ifndef P_WINDOWS_FACTORY
#define P_WINDOWS_FACTORY

#include <game/platform/platform_factory.h>
#include <game/platform/windows/window.h>
#include <game/platform/windows/renderer.h>
#include <game/platform/windows/assetmanager.h>

namespace punkyoi::platform::windows {

    class WindowsFactory : public ::punkyoi::platform::PlatformFactory {
        virtual ::punkyoi_api::IWindow* createWindow(const ::punkyoi_api::WindowProps& properties, ::std::shared_ptr<::punkyoi_api::events::EventBus> eventBus) override;
        virtual ::punkyoi_api::WindowProps getDefaultWindowProps() override;
        virtual ::punkyoi_api::IRenderer* createRenderer() override;
        virtual ::punkyoi_api::IAssetManager* createAssetManager() override;
    };
}


#endif
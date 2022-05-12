#ifndef P_APP
#define P_APP

#include <game/core.h>
#include <game/common/exception.h>
#include <stdexcept>
#include <game/platform/platform.h>
#include <chrono>
#include <game/events/game_events.h>
#include <game/concrete/dinoworldprovider.h>
#include <game/singleton.h>

namespace punkyoi {

    using punkyoi_api::log;

    class Punkyoi : public punkyoi_api::events::EventListener<events::WindowClosedEvent> {
    public:
        static Punkyoi& getPunkyoi();
        static Punkyoi& createPunkyoi();
        void run();

        virtual void onEvent(events::WindowClosedEvent& event) override;

        ::punkyoi_api::IAssetManager& getAssetManager();
        ::punkyoi_api::ISoundEngine& getSoundEngine();
        ::punkyoi_api::events::EventBus& getEventBus();
        
    protected:
        Punkyoi();

        std::shared_ptr<punkyoi_api::IWindow> m_window;
        std::shared_ptr<punkyoi_api::IRenderer> m_renderer;
        std::shared_ptr<punkyoi_api::IAssetManager> m_assetManager;
        std::shared_ptr<punkyoi_api::events::EventBus> m_eventBus;
        std::shared_ptr<punkyoi_api::ISoundEngine> m_soundEngine;
        bool m_isRunning;

    public:
        virtual ~Punkyoi();

    private:
        static std::unique_ptr<Punkyoi> s_instance;
    };
}

#endif

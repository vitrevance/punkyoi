#include "app.h"

namespace punkyoi {

    std::unique_ptr<Punkyoi> Punkyoi::s_instance = nullptr;

    Punkyoi& Punkyoi::getPunkyoi() {
        if (!s_instance) {
            throw common::exceptions::RuntimeException("Game instance must be initialized before any logic!");
        }
        return *s_instance;
    }

    Punkyoi& Punkyoi::createPunkyoi() {
        if (s_instance) {
            throw common::exceptions::RuntimeException("Create method is only for initial instantiation! Use getPunkyoi() instead!");
        }
        s_instance = std::unique_ptr<Punkyoi>(new Punkyoi());
        return *s_instance;
    }

    void Punkyoi::onEvent(events::WindowClosedEvent& event) {
        m_isRunning = false;
    }

    Punkyoi::Punkyoi() {
    }
    
    void Punkyoi::run() {
        log::console() << "Punkyoi started" << log::endl;
        m_eventBus = std::make_shared<punkyoi_api::events::EventBus>();
        m_eventBus->subscribeEventListener(this);

        m_assetManager = std::shared_ptr<punkyoi_api::IAssetManager>(platform::Platform().createAssetManager());
        m_assetManager->loadAssetMap("assets/assets.json");
        m_window = std::shared_ptr<punkyoi_api::IWindow>(
            platform::Platform().createWindow(
                punkyoi::platform::Platform().getDefaultWindowProps(),
                m_eventBus)
            );
        m_renderer = std::shared_ptr<punkyoi_api::IRenderer>(platform::Platform().createRenderer());
        m_renderer->init(m_window.get());
        m_soundEngine = std::make_shared<common::SoundEngine>(::punkyoi::getAssetManager());

        m_isRunning = true;

        std::shared_ptr<common::IWorldProvider> worldProvider = std::make_shared<concrete::DinoWorldProvider>();
        worldProvider->init();
        std::shared_ptr<common::World> world = worldProvider->createWorld(*m_eventBus);

        typedef std::chrono::high_resolution_clock clock;
        typedef std::chrono::duration<float, std::milli> duration;

        static clock::time_point start = clock::now();
        duration elapsed = clock::now() - start;

        while (m_isRunning) {
            if (m_window != nullptr) {
                m_window->onUpdate();
                m_window->onRenderPre();
                m_renderer->onRenderPre();
                events::RenderEvent renderEvent(*static_cast<punkyoi_api::IRenderContext*>(m_renderer.get()));
                m_eventBus->postEvent(renderEvent);
                m_renderer->onRenderPost();
                m_window->onRenderPost();
            }
            elapsed = clock::now() - start;
            if (elapsed.count() > 1) {
                events::TickEvent tickEvent(elapsed.count() / 1000.0f);
                m_eventBus->postEvent(tickEvent);
                start = clock::now();
            }
        }

        m_renderer->deinit();
    }

    Punkyoi::~Punkyoi() {
        log::console() << "Punkyoi destroyed" << log::endl;
    }

    ::punkyoi_api::IAssetManager& Punkyoi::getAssetManager() {
        return *m_assetManager;
    }

    ::punkyoi_api::ISoundEngine& Punkyoi::getSoundEngine() {
        return *m_soundEngine;
    }

    ::punkyoi_api::events::EventBus& Punkyoi::getEventBus() {
        return *m_eventBus;
    }

    common::AssetManager& getAssetManager() {
        return dynamic_cast<common::AssetManager&>(Punkyoi::getPunkyoi().getAssetManager());
    }

    common::SoundEngine& getSoundEngine() {
        return dynamic_cast<common::SoundEngine&>(Punkyoi::getPunkyoi().getSoundEngine());
    }

    ::punkyoi_api::events::EventBus& getEventBus() {
        return Punkyoi::getPunkyoi().getEventBus();
    }
}
#ifndef P_APP
#define P_APP

#include <game/core.h>
#include <stdexcept>
#include <game/platform/platform.h>
#include <chrono>
#include <game/events/game_events.h>
#include <game/concrete/dinoworldprovider.h>

namespace punkyoi {

    using punkyoi_api::log;

    class Punkyoi : public punkyoi_api::events::EventListener<events::WindowClosedEvent> {
    public:
        static Punkyoi& getPunkyoi() {
            if (!s_instance) {
                throw std::runtime_error("Game instance must be initialized before any logic!");
            }
            return *s_instance;
        }

        static Punkyoi& createPunkyoi() {
            if (s_instance) {
                throw std::runtime_error("Create method is only for initial instantiation! Use getPunkyoi() instead!");
            }
            s_instance = std::unique_ptr<Punkyoi>(new Punkyoi());
            return *s_instance;
        }

        virtual void onEvent(events::WindowClosedEvent& event) override {
            m_isRunning = false;
        }
        
    protected:
        Punkyoi() {
            log::console() << "Punkyoi created" << log::endl;
            m_eventBus = std::make_shared<punkyoi_api::events::EventBus>();
            m_eventBus->subscribeEventListener(this);
            m_window = std::shared_ptr<punkyoi_api::IWindow>(
                platform::Platform().createWindow(
                    punkyoi::platform::Platform().getDefaultWindowProps(),
                    m_eventBus)
                );
            m_isRunning = true;

            std::shared_ptr<common::IWorldProvider> worldProvider = std::make_shared<concrete::DinoWorldProvider>();
            worldProvider->init();
            std::shared_ptr<common::World> world = worldProvider->createWorld(*m_eventBus);

            typedef std::chrono::high_resolution_clock clock;
            typedef std::chrono::duration<float, std::milli> duration;

            static clock::time_point start = clock::now();
            duration elapsed = clock::now() - start;

            while (m_isRunning) {
                if (this->m_window != nullptr) {
                    this->m_window->onUpdate();
                    this->m_window->onRenderPre();
                    //this->m_renderer->onRenderPre();
                    //this->m_activeScene->render(this->m_renderer);
                    //this->m_renderer->onRenderPost();
                    this->m_window->onRenderPost();
                }
                elapsed = clock::now() - start;
                if (elapsed.count() > 1) {
                    events::TickEvent tickEvent(elapsed.count());
                    m_eventBus->postEvent(tickEvent);
                    start = clock::now();
                }
            }
        }

        std::shared_ptr<punkyoi_api::IWindow> m_window;
        std::shared_ptr<punkyoi_api::events::EventBus> m_eventBus;
        bool m_isRunning;

    public:
        virtual ~Punkyoi() {
            log::console() << "Punkyoi destroyed" << log::endl;
        }

    private:
        static std::unique_ptr<Punkyoi> s_instance;
    };

    std::unique_ptr<Punkyoi> Punkyoi::s_instance = nullptr;
}

#endif

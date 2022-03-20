#ifndef P_APP
#define P_APP

#include <game/core.h>
#include <stdexcept>
#include <game/platform/platform.h>

namespace punkyoi {

    using punkyoi_api::log;

    class Punkyoi {
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

    
        
    protected:
        Punkyoi() {
            log::console() << "Punkyoi created" << log::endl;
            m_window = std::shared_ptr<punkyoi_api::IWindow>(
                platform::Platform().createWindow(
                    punkyoi::platform::Platform().getDefaultWindowProps(),
                    m_eventBus)
                );
        }

        std::shared_ptr<punkyoi_api::IWindow> m_window;
        std::shared_ptr<punkyoi_api::events::EventBus> m_eventBus;

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

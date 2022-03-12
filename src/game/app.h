#pragma once

#include <stdexcept>
#include <memory>

#include <api/utils/logger.h>

namespace game {

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
                return *s_instance;
            }
            s_instance = std::unique_ptr<Punkyoi>(new Punkyoi());
            return *s_instance;
        }

    public:
        virtual ~Punkyoi() {
            log::console() << "Punkyoi destroyed" << log::endl;
        }
        
    protected:
        Punkyoi() {
            log::console() << "Punkyoi created" << log::endl;
        }

        static std::unique_ptr<Punkyoi> s_instance;
    };

    std::unique_ptr<Punkyoi> Punkyoi::s_instance = nullptr;
}
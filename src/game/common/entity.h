#ifndef P_ENTITY
#define P_ENTITY

#include <game/core.h>
#include <game/events/game_events.h>

namespace punkyoi::common {

    class Entity : public punkyoi_api::events::EventListener<punkyoi::events::TickEvent> {
    public:
        Entity();
        virtual ~Entity();

        virtual void onDeath();
        virtual bool isDead() const;
        virtual void onEvent(punkyoi::events::TickEvent&) override;

    protected:
        bool m_isDead;
    };
}

#endif
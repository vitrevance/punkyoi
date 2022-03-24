#ifndef P_ENTITYPLAYER
#define P_ENTITYPLAYER

#include <game/core.h>
#include <game/common/entityblueprint.h>

namespace punkyoi::concrete {

    class EntityPlayer : public ::punkyoi::common::EntityBasicRenderable,
        public ::punkyoi_api::events::EventListener<::punkyoi::events::KeyPressedEvent>,
        public ::punkyoi_api::events::EventListener<::punkyoi::events::KeyReleasedEvent> {
    public:
        EntityPlayer(::punkyoi::common::Scene&);
        ~EntityPlayer();

        vec2 getVelocity();
        void setVelocity(vec2);

        virtual void onEvent(::punkyoi::events::KeyPressedEvent& event) override;
        virtual void onEvent(::punkyoi::events::KeyReleasedEvent& event) override;
        virtual void onEvent(::punkyoi::events::TickEvent& event) override;

    protected:
        vec2 m_velocity;
        float m_lifetime;
        int m_direction;
    };
}

#endif
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
        vec2 m_speed;
        bool m_isJumping;
    };

    class EntityCacti : public ::punkyoi::common::EntityBasicRenderable {
    public:
        EntityCacti(::punkyoi::common::Scene&);
        ~EntityCacti();
        virtual void addAttribute(int attribute);
        virtual ::punkyoi_api::IRenderBase& getRenderer() override;

        friend class CactiRenderer;

    protected:
        int m_attribute = -1;
    };

    class CactiRenderer : public ::punkyoi_api::IRender<EntityCacti> {
    public:
        virtual ~CactiRenderer() = default;
        virtual void render(EntityCacti&, ::punkyoi_api::IRenderContext&) override;
    };
}

#endif
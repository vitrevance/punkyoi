#ifndef P_ENTITYPLAYER
#define P_ENTITYPLAYER

#include <game/core.h>
#include <game/common/entityblueprint.h>
#include <game/common/input.h>

namespace punkyoi::concrete {

    class EntityPlayer : public ::punkyoi::common::EntityBasicRenderable,
        public ::punkyoi_api::events::EventListener<::punkyoi::events::KeyPressedEvent>,
        public ::punkyoi_api::events::EventListener<::punkyoi::events::KeyReleasedEvent> {
    public:
        using Input = ::punkyoi::common::Input;
        EntityPlayer(::punkyoi::common::Scene&);
        ~EntityPlayer();

        vec2 getVelocity();
        void setVelocity(vec2);

        virtual void onDeath() override;

        virtual void onEvent(::punkyoi::events::KeyPressedEvent& event) override;
        virtual void onEvent(::punkyoi::events::KeyReleasedEvent& event) override;
        virtual void onEvent(::punkyoi::events::TickEvent& event) override;

    protected:
        vec2 m_velocity = vec2(0);
        float m_lifetime = 0;
        vec2 m_speed = vec2(0);
        bool m_isJumping = false;
    };

    class EntityCacti : public ::punkyoi::common::EntityBasicRenderable {
    public:
        EntityCacti(::punkyoi::common::Scene&);
        virtual ~EntityCacti();
        virtual void addAttribute(int attribute);
        virtual ::punkyoi_api::IRenderBase& getRenderer() override;
        virtual void watchPlayer(const object<EntityPlayer>&);
        virtual void onEvent(::punkyoi::events::TickEvent&) override;

        friend class CactiRenderer;

    protected:
        int m_attribute = -1;
        object<EntityPlayer> m_player;
    };

    class CactiRenderer : public ::punkyoi_api::IRender<EntityCacti> {
    public:
        virtual ~CactiRenderer() = default;
        virtual void render(EntityCacti&, ::punkyoi_api::IRenderContext&) override;
    };

    class EntityGround : public ::punkyoi::common::EntityBasicRenderable {
    public:
        EntityGround(::punkyoi::common::Scene&, object<EntityPlayer>, int);
        virtual ~EntityGround();

        virtual void onEvent(::punkyoi::events::TickEvent&) override;
    protected:
        object<EntityPlayer> m_thePlayer;
        int m_atlasSize = 2;
    };

    class EntityMisc : public ::punkyoi::common::EntityBasicRenderable {
    public:
        template<typename Lambda, typename...Args>
        EntityMisc(Lambda&& callback, Args&&...args) : ::punkyoi::common::EntityBasicRenderable(std::forward<Args>(args)...), m_callback(callback) {
        }

        virtual void onEvent(::punkyoi::events::TickEvent&) override;
    protected:
        std::function<void(::punkyoi::events::TickEvent&, EntityMisc*)> m_callback;
    };
}

#endif
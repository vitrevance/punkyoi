#ifndef P_ENTITYBLUEPRINT
#define P_ENTITYBLUEPRINT

#include <game/core.h>
#include <game/common/entity.h>
#include <api/irender.h>
#include <game/events/game_events.h>

namespace punkyoi::common {

    class EntityBasicRenderable : public Entity, ::punkyoi_api::events::EventListener<::punkyoi::events::RenderEvent> {
    public:
        EntityBasicRenderable(vec2, const std::string&);
        virtual ~EntityBasicRenderable() = default;

        virtual void onEvent(::punkyoi::events::RenderEvent&) override;
        virtual ::punkyoi_api::IRenderBase& getRenderer();
    protected:
        std::string m_textureName;
        vec2 m_size;
    };

    class EntityBasicRenderableRenderer : public ::punkyoi_api::IRender<EntityBasicRenderable> {
    public:
        virtual ~EntityBasicRenderableRenderer() = default;
        virtual void render(EntityBasicRenderable&, ::punkyoi_api::IRenderContext&) override;
    };
}

#endif
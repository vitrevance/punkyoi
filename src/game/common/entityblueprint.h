#ifndef P_ENTITYBLUEPRINT
#define P_ENTITYBLUEPRINT

#include <game/core.h>
#include <game/common/entity.h>
#include <api/irender.h>
#include <game/events/game_events.h>
#include <game/common/assetmanager.h>
#include <game/singleton.h>

namespace punkyoi::common {

    class EntityBasicRenderable : public Entity, ::punkyoi_api::events::EventListener<::punkyoi::events::RenderEvent> {
    public:
        EntityBasicRenderable(Scene&, vec2, const std::string&, int frames = 1);
        virtual ~EntityBasicRenderable() = default;

        virtual void onEvent(::punkyoi::events::RenderEvent&) override;
        virtual ::punkyoi_api::IRenderBase& getRenderer();

        virtual vec2& getPosition();
        virtual vec2& getScale();
        virtual const std::string& getTexture();
        virtual int getTextureIndex();
        virtual int getTextureFrames();
    protected:
        std::string m_textureName;
        int m_textureFrames;
        int m_textureIndex;
        vec2 m_size;
        vec2 m_position;
    };

    class EntityBasicRenderableRenderer : public ::punkyoi_api::IRender<EntityBasicRenderable> {
    public:
        virtual ~EntityBasicRenderableRenderer() = default;
        virtual void render(EntityBasicRenderable&, ::punkyoi_api::IRenderContext&) override;
    };
}

#endif
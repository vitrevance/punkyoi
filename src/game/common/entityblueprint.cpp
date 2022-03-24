#include "entityblueprint.h"

namespace punkyoi::common {

    EntityBasicRenderable::EntityBasicRenderable(Scene& scene, vec2 size, const std::string& name, int frames)
        : Entity(scene), m_size(size), m_textureName(name), m_textureFrames(frames), m_textureIndex(0) {
    }

    vec2 EntityBasicRenderable::getPosition() {
        return m_position;
    }

    vec2 EntityBasicRenderable::getScale() {
        return m_size;
    }

    int EntityBasicRenderable::getTextureIndex() {
        return m_textureIndex;
    }

    int EntityBasicRenderable::getTextureFrames() {
        return m_textureFrames;
    }

    const std::string& EntityBasicRenderable::getTexture() {
        return m_textureName;
    }

    void EntityBasicRenderable::onEvent(::punkyoi::events::RenderEvent& event) {
        ::punkyoi_api::IRenderContext& context = event.getContext();
        ::punkyoi_api::IRenderBase& render = getRenderer();
        render.render(this, context);
    }

    ::punkyoi_api::IRenderBase& EntityBasicRenderable::getRenderer() {
        static EntityBasicRenderableRenderer renderer;
        return renderer;
    }

    void EntityBasicRenderableRenderer::render(EntityBasicRenderable& target, ::punkyoi_api::IRenderContext& context) {
        context.push();
        context.scale(target.getScale());
        context.translate(target.getPosition() - target.getScale() * 0.5);
        std::string texture = target.getTexture();
        if (target.getTextureFrames() > 1) {
            texture += std::to_string(target.getTextureIndex() % target.getTextureFrames());
        }
        ImageAsset& asset = static_cast<ImageAsset&>(getAssetManager().getAsset(texture));
        context.drawImage(asset);
        context.pop();
    }
}
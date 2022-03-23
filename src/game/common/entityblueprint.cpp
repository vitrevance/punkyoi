#include "entityblueprint.h"

namespace punkyoi::common {

    EntityBasicRenderable::EntityBasicRenderable(vec2 size, const std::string& name) : m_size(size), m_textureName(name) {

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
        
    }
}
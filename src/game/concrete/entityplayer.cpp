#include "entityplayer.h"

namespace punkyoi::concrete {

    EntityPlayer::EntityPlayer(::punkyoi::common::Scene& scene) : common::EntityBasicRenderable(scene, vec2(1, 1), "sprite.dino", 6) {
        m_speed = vec2(1, 11);
        m_position = vec2(1, 0);
    }

    EntityPlayer::~EntityPlayer() {
    }

    vec2 EntityPlayer::getVelocity() {
        return m_velocity;
    }

    void EntityPlayer::setVelocity(vec2 v) {
        m_velocity = v;
    }

    void EntityPlayer::onEvent(::punkyoi::events::KeyPressedEvent& event) {
        if (event.getKeyCode() == 87 && m_position.y <= 0.1) {
            m_isJumping = true;
            m_velocity.y = m_speed.y;
        }
    }

    void EntityPlayer::onEvent(::punkyoi::events::KeyReleasedEvent& event) {
        if (event.getKeyCode() == 87) {
            m_isJumping = false;
        }
    }

    void EntityPlayer::onEvent(::punkyoi::events::TickEvent& event) {
        m_speed.x = log2(m_position.x) / 2 + 1;
        m_velocity.x = m_speed.x;
        if (m_isJumping && m_velocity.y > 0) {
            m_velocity.y += -30 * event.getDeltaTime();
        }
        else {
            m_velocity.y += -50 * event.getDeltaTime();
        }
        m_position += m_velocity * event.getDeltaTime();
        if (m_position.y < 0) {
            m_position.y = 0;
            if (m_velocity.y < 0) {
                m_velocity.y = 0;
            }
        }
        m_lifetime += event.getDeltaTime();
        if (m_lifetime > 0.5 / m_velocity.x) {
            m_lifetime = 0;
            ++m_textureIndex;
        }
        m_textureIndex %= m_textureFrames;
    }

    EntityCacti::EntityCacti(::punkyoi::common::Scene& scene) : ::punkyoi::common::EntityBasicRenderable(scene, vec2(1), "sprite.cacti_h") {
    }

    EntityCacti::~EntityCacti() {
    }

    void EntityCacti::addAttribute(int attribute) {
        m_attribute = attribute;
    }

    ::punkyoi_api::IRenderBase& EntityCacti::getRenderer() {
        static CactiRenderer renderer;
        return renderer;
    }

    void CactiRenderer::render(EntityCacti& target, ::punkyoi_api::IRenderContext& context) {
        context.push();

        context.translate(target.getPosition() + vec2(0, target.getScale().y / 2));
        context.scale(target.getScale());
        auto& base_img = dynamic_cast<::punkyoi_api::IImage&>(getAssetManager().getAsset(target.getTexture()));
        auto& hands_img = dynamic_cast<::punkyoi_api::IImage&>(getAssetManager().getAsset("sprite.cacti_m"));
        context.drawImage(hands_img);
        context.drawImage(base_img);

        if (target.m_attribute >= 0) {
            context.push();

            auto& attr_img = dynamic_cast<::punkyoi_api::IImage&>(getAssetManager().getAsset("sprite.attrib_" + ::std::to_string(target.m_attribute)));
            context.translate(vec2(0.025, -0.05));
            context.scale(vec2(0.2));
            context.drawImage(attr_img);

            context.pop();
        }

        context.pop();
    }
}
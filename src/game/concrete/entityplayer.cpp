#include "entityplayer.h"

namespace punkyoi::concrete {

    EntityPlayer::EntityPlayer(::punkyoi::common::Scene& scene) : common::EntityBasicRenderable(scene, vec2(1, 1), "sprite.player_idle", 6) {
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
        if (event.getRepeatCount() != 0) {
            return;
        }
        if (event.getKeyCode() == 68) {
            m_direction = 1;
        }
        if (event.getKeyCode() == 65) {
            m_direction = -1;
        }
        if (event.getKeyCode() == 87 && m_position.y <= 0.001) {
            m_velocity.y = 0.1;
        }
    }

    void EntityPlayer::onEvent(::punkyoi::events::KeyReleasedEvent& event) {
        if (event.getKeyCode() == 68 && m_direction == 1) {
            m_direction = 0;
        }
        if (event.getKeyCode() == 65 && m_direction == -1) {
            m_direction = 0;
        }
    }

    void EntityPlayer::onEvent(::punkyoi::events::TickEvent& event) {
        m_velocity += vec2(0, -0.2) * event.getDeltaTime();
        m_position += m_velocity;
        if (m_position.y < 0) {
            m_position.y = 0;
            if (m_velocity.y < 0) {
                m_velocity.y = 0;
            }
        }
        if (m_direction == 0) {
            m_textureName = "sprite.player_idle";
            m_textureFrames = 6;
        }
        else {
            if (m_direction < 0) {
                m_size.x = -1;
            }
            else {
                m_size.x = 1;
            }
            m_textureName = "sprite.player_run";
            m_textureFrames = 8;
        }
        m_lifetime += event.getDeltaTime();
        if (m_lifetime > 0.15) {
            m_lifetime = 0;
            ++m_textureIndex;
        }
        m_textureIndex %= m_textureFrames;
        m_velocity.x = 0.05 * m_direction;
    }
}
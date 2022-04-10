#include "levelcontroller.h"

namespace punkyoi::concrete {

    LevelController::LevelController(::punkyoi::common::Scene& scene) : ::punkyoi::common::Entity(scene), m_scene(scene) {
    }

    void LevelController::addPlayer(const object<EntityPlayer>& player) {
        m_players.push_back(player);
    }

    void LevelController::setThePlayer(const object<EntityPlayer>& player) {
        m_thePlayer = player;
        m_cameraPosition = player->getPosition();
        m_cameraPosition.y = 1.2;
    }

    void LevelController::onEvent(::punkyoi::events::TickEvent& event) {
        if (rand() % 28 == 1 && m_misc < 150) {
            object<EntityMisc> misc = new_instance<EntityMisc>([this](::punkyoi::events::TickEvent& event, EntityMisc* self) {
                if (self->getPosition().x < this->m_thePlayer->getPosition().x - 3) {
                    self->setDead(true);
                    --this->m_misc;
                }
                }, m_scene, vec2(0.05 + (float(rand() % 100) / 190.0)), "sprite.misc_" + std::to_string(rand() % 7));
            misc->getPosition() = vec2(m_thePlayer->getPosition().x + 50 + (rand() % 10) * m_thePlayer->getScale().x, -0.1 - (rand() % 100) / 100.0);
            m_scene.addEntity(misc);
            ++m_misc;
        }
    }

    void LevelController::onEvent(punkyoi::events::RenderEvent& event) {
        if (!m_thePlayer) {
            return;
        }
        if (m_cameraPosition.x < m_thePlayer->getPosition().x + 2.5) {
            m_cameraPosition.x = m_thePlayer->getPosition().x + 2.5;
        }
        event.getContext().scale(vec2(0.25, 0.25));
        event.getContext().push();
        event.getContext().translate(vec2(-m_cameraPosition.x, -m_cameraPosition.y));
    }
}
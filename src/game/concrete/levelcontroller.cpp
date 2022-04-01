#include "levelcontroller.h"

namespace punkyoi::concrete {

    LevelController::LevelController(::punkyoi::common::Scene& scene) : ::punkyoi::common::Entity(scene) {
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
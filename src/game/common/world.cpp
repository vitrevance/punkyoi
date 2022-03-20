#include "world.h"

namespace punkyoi::common {

    World::World(punkyoi_api::events::EventBus& parentBus) {
        m_eventBus = std::make_shared<punkyoi_api::events::EventBus>();
        m_eventBus->subscribeEventListener(this);
        parentBus.attachEventBus(m_eventBus);
    }

    World::~World() {
        m_eventBus->unsubscribeEventListener(this);
        for (auto& scene : m_scenes) {
            m_eventBus->detachEventBus(scene->getEventBus());
            scene->unload();
        }
    }

    void World::onEvent(punkyoi::events::TickEvent& event) {
        for (std::list<std::shared_ptr<Scene> >::iterator it = m_scenes.begin(); it != m_scenes.end(); ++it) {
            if (!(*it)->isActive()) {
                m_eventBus->detachEventBus((*it)->getEventBus());
                (*it)->unload();
                m_scenes.erase(it++);
                --it;
            }
        }
    }

    void World::pushScene(std::shared_ptr<Scene>& scene) {
        m_scenes.push_back(scene);
        m_eventBus->attachEventBus(scene->getEventBus());
        scene->load();
    }
}
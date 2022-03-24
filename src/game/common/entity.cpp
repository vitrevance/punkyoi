#include "entity.h"

namespace punkyoi::common {

    Entity::Entity(Scene& scene) : m_isDead(false), m_scene(scene) {}
    Entity::~Entity() {}

    void Entity::onEvent(::punkyoi::events::TickEvent& event) {}

    void Entity::onDeath() {}

    bool Entity::isDead() const {
        return m_isDead;
    }

}
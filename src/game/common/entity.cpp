#include "entity.h"

namespace punkyoi::common {

    Entity::Entity() : m_isDead(false) {}
    Entity::~Entity() {}

    void Entity::onEvent(::punkyoi::events::TickEvent& event) {}

    void Entity::onDeath() {}

    bool Entity::isDead() const {
        return m_isDead;
    }

}
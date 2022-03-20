#include "entityenemy.h"

namespace punkyoi::concrete {

    EntityEnemy::EntityEnemy() {
        log::console() << "creating entity enemy" << log::endl;
    }
    EntityEnemy::~EntityEnemy() {
        log::console() << "deleting entity enemy" << log::endl;
    }

    void EntityEnemy::onEvent(::punkyoi::events::KeyPressedEvent& event) {
        log::console() << "onEvent<KeyPressedEvent>: " << event.getKeyCode() << " " << event.getRepeatCount() << log::endl;
    }
}
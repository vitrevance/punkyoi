#include "entityplayer.h"

namespace punkyoi::concrete {

    EntityPlayer::EntityPlayer() : common::EntityBasicRenderable(vec2(1, 1), "texture_name") {
        log::console() << "creating entity player" << log::endl;
    }
    EntityPlayer::~EntityPlayer() {
        log::console() << "deleting entity player" << log::endl;
    }

    void EntityPlayer::onEvent(::punkyoi::events::KeyPressedEvent& event) {
        log::console() << "onEvent<KeyPressedEvent>: " << event.getKeyCode() << " " << event.getRepeatCount() << log::endl;
    }
}
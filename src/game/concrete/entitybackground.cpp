#include "entitybackground.h"

namespace punkyoi::concrete {

    EntityBackground::EntityBackground(::punkyoi::common::Scene& scene) : ::punkyoi::common::Entity(scene) {
    }

    EntityBackground::~EntityBackground() {
    }

    void EntityBackground::onEvent(punkyoi::events::RenderEvent& event) {
    }
}
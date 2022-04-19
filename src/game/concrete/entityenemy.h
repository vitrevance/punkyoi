#ifndef P_ENTITYENEMY
#define P_ENTITYENEMY

#include <game/core.h>
#include <game/common/entity.h>

namespace punkyoi::concrete {

    class EntityEnemy : public ::punkyoi::common::Entity, ::punkyoi_api::events::EventListener<::punkyoi::events::KeyPressedEvent> {
    public:
        EntityEnemy();
        ~EntityEnemy();

        virtual void onEvent(::punkyoi::events::KeyPressedEvent& event) override;
    };
}

#endif
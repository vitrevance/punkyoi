#ifndef P_ENTITYPLAYER
#define P_ENTITYPLAYER

#include <game/core.h>
#include <game/common/entityblueprint.h>

namespace punkyoi::concrete {

    class EntityPlayer : public ::punkyoi::common::EntityBasicRenderable, ::punkyoi_api::events::EventListener<::punkyoi::events::KeyPressedEvent> {
    public:
        EntityPlayer();
        ~EntityPlayer();

        virtual void onEvent(::punkyoi::events::KeyPressedEvent& event) override;
    };
}

#endif
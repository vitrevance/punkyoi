#ifndef P_ENTITYBACKGROUND
#define P_ENTITYBACKGROUND

#include <game/core.h>
#include <game/common/entity.h>

namespace punkyoi::concrete {

    class EntityBackground : public ::punkyoi::common::Entity, public ::punkyoi_api::events::EventListener<::punkyoi::events::RenderEvent> {
    public:
        EntityBackground(::punkyoi::common::Scene&);
        virtual ~EntityBackground();

        virtual void onEvent(::punkyoi::events::RenderEvent&) override;
    };
}

#endif
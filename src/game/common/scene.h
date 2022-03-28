#ifndef P_SCENE
#define P_SCENE

#include <game/core.h>
#include <api/events/eventbus.h>
#include <game/common/entity.h>
#include <list>

namespace punkyoi::common {

    class Scene : public punkyoi_api::events::EventListener<::punkyoi::events::TickEvent> {
    public:
        Scene();
        virtual ~Scene();

        virtual bool isActive();
        virtual void close();
        virtual void load();
        virtual void unload();
        virtual void addEntity(const object<Entity>& entity);

        virtual void onEvent(::punkyoi::events::TickEvent& event) override;

        virtual std::shared_ptr<::punkyoi_api::events::EventBus>& getEventBus();

    protected:
        bool m_isActive;
        std::shared_ptr<::punkyoi_api::events::EventBus> m_eventBus;
        std::list<object<Entity> > m_entities;
    };
}

#endif
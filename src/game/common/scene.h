#ifndef P_SCENE
#define P_SCENE

#include <game/core.h>
#include <api/events/eventbus.h>
#include <game/common/entity.h>
#include <list>

namespace punkyoi::common {

    class Scene : public punkyoi_api::events::EventListener<punkyoi::events::TickEvent> {
    public:
        Scene();
        ~Scene();

        bool isActive();
        void close();
        virtual void load();
        virtual void unload();
        virtual void addEntity(const std::shared_ptr<Entity>& entity);

        virtual void onEvent(punkyoi::events::TickEvent& event) override;

        std::shared_ptr<punkyoi_api::events::EventBus>& getEventBus();

    protected:
        bool m_isActive;
        std::shared_ptr<punkyoi_api::events::EventBus> m_eventBus;
        std::list<std::shared_ptr<Entity> > m_entities;
    };
}

#endif
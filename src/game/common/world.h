#ifndef P_WORLD
#define P_WORLD

#include <game/core.h>
#include <list>
#include <game/common/scene.h>
#include <api/events/eventbus.h>
#include <game/events/game_events.h>
#include <api/irender.h>

namespace punkyoi::common {

    class World : public punkyoi_api::events::EventListener<punkyoi::events::TickEvent> {
    public:
        World(punkyoi_api::events::EventBus& parentBus);
        ~World();

        virtual void onEvent(punkyoi::events::TickEvent& event) override;
        void pushScene(std::shared_ptr<Scene>& scene);

    protected:
        std::list<std::shared_ptr<Scene> > m_scenes;
        std::shared_ptr<punkyoi_api::events::EventBus> m_eventBus;
    };
}

#endif
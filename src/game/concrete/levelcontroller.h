#ifndef P_AABBCOLLISIONCONTROLLER
#define P_AABBCOLLISIONCONTROLLER

#include <game/core.h>
#include <game/concrete/entityplayer.h>

namespace punkyoi::concrete {

    class LevelController : public ::punkyoi::common::Entity, public ::punkyoi_api::events::EventListener<::punkyoi::events::RenderEvent> {
    public:
        LevelController(::punkyoi::common::Scene&);
        virtual ~LevelController() = default;

        void addPlayer(const object<EntityPlayer>&);
        void setThePlayer(const object<EntityPlayer>&);

        virtual void onEvent(::punkyoi::events::TickEvent&) override;
        virtual void onEvent(::punkyoi::events::RenderEvent&) override;
    
    protected:
        std::vector<object<EntityPlayer> > m_players;
        object<EntityPlayer> m_thePlayer;
        vec2 m_cameraPosition;
    };
}

#endif
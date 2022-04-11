#ifndef P_PUNKYOI_WORLD
#define P_PUNKYOI_WORLD

#include <game/core.h>
#include <game/common/world.h>
#include <game/concrete/uiscreen.h>
#include <game/concrete/levelcontroller.h>

namespace punkyoi::concrete {

    class MainMenu : public UIScreen {
    public:
        MainMenu();
        ~MainMenu();

        virtual void load(::punkyoi::common::World& world) override;
        virtual void unload() override;
    protected:
        ::punkyoi::common::World* m_world;
    };

    class DinoLevel : public ::punkyoi::common::Scene {
    public:
        DinoLevel();
        ~DinoLevel();

        virtual void load(::punkyoi::common::World&) override;
        virtual void unload() override;
    };

    class DinoWorld : public ::punkyoi_api::events::EventListener<::punkyoi::events::GameStateEvent>, public ::punkyoi::common::World {
    public:
        DinoWorld(::punkyoi_api::events::EventBus&);

        virtual ~DinoWorld();

        virtual void onEvent(::punkyoi::events::TickEvent& event) override;
        virtual void onEvent(::punkyoi::events::GameStateEvent& event) override;

    protected:
        std::shared_ptr<MainMenu> m_mainMenu;
        std::shared_ptr<::punkyoi::common::Scene> m_level;
    };
}

#endif
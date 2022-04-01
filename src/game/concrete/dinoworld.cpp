#include "dinoworld.h"

namespace punkyoi::concrete {

    MainMenu::MainMenu() {
    }

    MainMenu::~MainMenu() {
    }

    void MainMenu::load(::punkyoi::common::World& world) {
        ::punkyoi::common::Scene::load(world);
        object<UIButton> playB = new_instance<UIButton>(*this, "ui.button.play", "ui.button.play_hover", vec2(0), vec2(0.3), [this]() {
            this->m_pendingState = 1;
            log::console() << "play" << log::endl;
        });
        addEntity(playB);
    }

    void MainMenu::unload() {
        UIScreen::unload();
        m_pendingState = 0;
    }

    size_t MainMenu::getState() {
        return m_pendingState;
    }

    DinoLevel::DinoLevel() {
    }

    DinoLevel::~DinoLevel() {
    }

    void DinoLevel::load(::punkyoi::common::World& world) {
        ::punkyoi::common::Scene::load(world);

        object<LevelController> levelController = new_instance<LevelController>(*this);
        object<EntityPlayer> player = new_instance<EntityPlayer>(*this);
        levelController->setThePlayer(player);

        addEntity(levelController);
        addEntity(player);
        
        for (int i = 0; i < 100; ++i) {
            object<EntityCacti> ent = new_instance<EntityCacti>(*this);
            ent->addAttribute(0);
            ent->getPosition() = vec2(i * 10 + (rand() % 20 - 10), 0);
            addEntity(ent);
        }
    }

    void DinoLevel::unload() {
        ::punkyoi::common::Scene::unload();
    }

    DinoWorld::DinoWorld(punkyoi_api::events::EventBus& parentBus) : ::punkyoi::common::World(parentBus) {
        m_mainMenu = std::make_shared<MainMenu>();
        m_level = std::make_shared<DinoLevel>();

        pushScene(m_mainMenu);
    }

    DinoWorld::~DinoWorld() {
    }

    void DinoWorld::onEvent(::punkyoi::events::TickEvent& event) {
        World::onEvent(event);
        if (m_mainMenu->getState() == 1) {
            m_mainMenu->close();
            pushScene(m_level);
        }
    }
}
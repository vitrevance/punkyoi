#include "dinoworld.h"

namespace punkyoi::concrete {

    MainMenu::MainMenu() {
    }

    MainMenu::~MainMenu() {
    }

    void MainMenu::load(::punkyoi::common::World& world) {
        ::punkyoi::common::Scene::load(world);
        object<::punkyoi::common::EntityBasicRenderable> background = new_instance<::punkyoi::common::EntityBasicRenderable>(*this, vec2(2), "ui.main_menu");
        background->getPosition().y = -background->getScale().y / 2;
        addEntity(background);
        object<UIButton> playB = new_instance<UIButton>(*this, "ui.button.play", "ui.button.play_hover", vec2(0), vec2(0.35), [this]() {
            ::punkyoi::events::GameStateEvent event(1);
            ::punkyoi::getEventBus().postEvent(event);
        });
        addEntity(playB);
    }

    void MainMenu::unload() {
        UIScreen::unload();
    }

    DinoLevel::DinoLevel() {
    }

    DinoLevel::~DinoLevel() {
    }

    void DinoLevel::load(::punkyoi::common::World& world) {
        ::punkyoi::common::Scene::load(world);

        object<EntityPlayer> player = new_instance<EntityPlayer>(*this);
        object<LevelController> levelController = new_instance<LevelController>(*this);
        levelController->setThePlayer(player);

        object<::punkyoi::common::EntityBasicRenderable> sky = new_instance<::punkyoi::common::EntityBasicRenderable>(*this, vec2(20), "sprite.sky");
        sky->getPosition().y = -sky->getScale().y / 2;
        addEntity(sky);
        object<::punkyoi::common::EntityBasicRenderable> sun = new_instance<::punkyoi::common::EntityBasicRenderable>(*this, vec2(0.3), "sprite.sun");
        sun->getPosition() = vec2(0.55, 0.2);
        addEntity(sun);

        addEntity(levelController);

        int backgroundAtlas = 5;
        for (int i = 0; i < backgroundAtlas; ++i) {
            object<EntityGround> ground = new_instance<EntityGround>(*this, player, backgroundAtlas);
            ground->getPosition() = vec2(ground->getScale().x * i, -ground->getScale().y / 4);
            addEntity(ground);
        }

        
        for (int i = 0; i < 500; ++i) {
            object<EntityCacti> ent = new_instance<EntityCacti>(*this);
            ent->addAttribute(0);
            ent->watchPlayer(player);
            ent->getPosition() = vec2(i * 10 + (rand() % 20 - 10), 0);
            addEntity(ent);
        }

        addEntity(player);
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
    }

    void DinoWorld::onEvent(::punkyoi::events::GameStateEvent& event) {
        if (event.getState() == 0 && m_level->isActive()) {
            m_level->close();
            pushScene(m_mainMenu);
        }
        if (event.getState() == 1 && m_mainMenu->isActive()) {
            m_mainMenu->close();
            pushScene(m_level);
        }
    }
}
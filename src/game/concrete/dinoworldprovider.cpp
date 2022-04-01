#include "dinoworldprovider.h"

namespace punkyoi::concrete {

    DinoWorldProvider::DinoWorldProvider() {
    }

    DinoWorldProvider::~DinoWorldProvider() {}

    void DinoWorldProvider::init() {}

    std::shared_ptr<::punkyoi::common::World> DinoWorldProvider::createWorld(punkyoi_api::events::EventBus& eventBus) {
        log::console() << "Creating world" << log::endl;
        std::shared_ptr<::punkyoi::common::World> world = std::make_shared<DinoWorld>(eventBus);

        //MAIN MENU
        //std::shared_ptr<MainMenu> mainMenuScreen = std::make_shared<MainMenu>();
        //world->pushScene(mainMenuScreen);
        //GAME ENV
        /*
        std::shared_ptr<::punkyoi::common::Scene> background = std::make_shared<::punkyoi::common::Scene>();
        std::shared_ptr<::punkyoi::common::Scene> scene = std::make_shared<::punkyoi::common::Scene>();
        world->pushScene(background);
        world->pushScene(scene);



        object<LevelController> level = new_instance<LevelController>(*scene);
        background->addEntity(level);

        object<EntityPlayer> player = new_instance<EntityPlayer>(*scene);
        level->setThePlayer(player);

        scene->addEntity(player);

        for (int i = 0; i < 100; ++i) {
            object<EntityCacti> ent = new_instance<EntityCacti>(*scene);
            ent->addAttribute(0);
            ent->getPosition() = vec2(i * 10 + (rand() % 20 - 10), 0);
            scene->addEntity(ent);
        }
        */
        return world;
    }
}
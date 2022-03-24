#include "dinoworldprovider.h"

namespace punkyoi::concrete {

    DinoWorldProvider::DinoWorldProvider() {
    }

    DinoWorldProvider::~DinoWorldProvider() {}

    void DinoWorldProvider::init() {}

    std::shared_ptr<::punkyoi::common::World> DinoWorldProvider::createWorld(punkyoi_api::events::EventBus& eventBus) {
        std::shared_ptr<::punkyoi::common::World> world = std::make_shared<::punkyoi::common::World>(eventBus);
        log::console() << "Creating world" << log::endl;

        std::shared_ptr<::punkyoi::common::Scene> background = std::make_shared<::punkyoi::common::Scene>();
        world->pushScene(background);

        std::shared_ptr<::punkyoi::common::Scene> scene = std::make_shared<::punkyoi::common::Scene>();
        world->pushScene(scene);

        object<EntityPlayer> player = new_instance<EntityPlayer>(*scene);
        object<common::EntityBasicRenderable> other = new_instance<common::EntityBasicRenderable>(*scene, vec2(1, 1), "sprite.block");
        scene->addEntity(player);
        scene->addEntity(other);

        object<LevelController> levelController = new_instance<LevelController>(*background);
        background->addEntity(levelController);
        levelController->setThePlayer(player);

        object<common::EntityBasicRenderable> ground = new_instance<common::EntityBasicRenderable>(*scene, vec2(20, 4), "sprite.ground");
        background->addEntity(ground);


        return world;
    }
}
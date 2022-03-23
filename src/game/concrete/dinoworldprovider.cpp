#include "dinoworldprovider.h"

namespace punkyoi::concrete {

    DinoWorldProvider::DinoWorldProvider() {
    }

    DinoWorldProvider::~DinoWorldProvider() {}

    void DinoWorldProvider::init() {}

    std::shared_ptr<::punkyoi::common::World> DinoWorldProvider::createWorld(punkyoi_api::events::EventBus& eventBus) {
        std::shared_ptr<::punkyoi::common::World> world = std::make_shared<::punkyoi::common::World>(eventBus);
        log::console() << "Creating world" << log::endl;

        std::shared_ptr<::punkyoi::common::Scene> scene = std::make_shared<::punkyoi::common::Scene>();
        world->pushScene(scene);

        object<EntityPlayer> player = new_instance<EntityPlayer>();

        scene->addEntity(player);

        return world;
    }
}
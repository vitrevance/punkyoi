#include "dinoworldprovider.h"

namespace punkyoi::concrete {

    DinoWorldProvider::DinoWorldProvider() {
    }

    DinoWorldProvider::~DinoWorldProvider() {}

    void DinoWorldProvider::init() {}

    std::shared_ptr<::punkyoi::common::World> DinoWorldProvider::createWorld(punkyoi_api::events::EventBus& eventBus) {
        std::shared_ptr<::punkyoi::common::World> world = std::make_shared<::punkyoi::common::World>(eventBus);
        log::console() << "Creating world" << log::endl;

        std::shared_ptr<UIScreen> mainMenuScreen = std::make_shared<UIScreen>();
        world->pushScene(mainMenuScreen);

        mainMenuScreen->addEntity(new_instance<UIButton>(*mainMenuScreen, "sprite.block", "sprite.ground", vec2(0.5, 0), vec2(0.2, 0.2), []() { log::console() << "pressed!" << log::endl; }));


        return world;
    }
}
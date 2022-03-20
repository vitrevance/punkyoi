
#include <game/core.h>

#if (CURRENT_PLATFORM == PLATFORM_LINUX)

#include <game/platform/linux/linux_factory.h>

namespace punkyoi::platform {

    std::unique_ptr<PlatformFactory> instance = nullptr;

    inline PlatformFactory& Platform() {
        if (instance.get() == nullptr) {
            instance = std::make_unique<linux::LinuxFactory>();
        }
        return *instance;
    }
}

#endif

#if (CURRENT_PLATFORM == PLATFORM_WINDOWS)

namespace punkyoi::platform {

    PlatformFactory& Platform() {
        std::static_assert(CURRENT_PLATFORM != PLATFORM_WINDOWS, "Windows is not supported yet!");
        throw std::runtime_error("Windows is not supported yet!");
    }
}

#endif
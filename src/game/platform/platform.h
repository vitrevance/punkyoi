
#include <game/core.h>

#if (CURRENT_PLATFORM == PLATFORM_LINUX)

#include <game/platform/linux/linux_factory.h>

namespace punkyoi::platform {

    static std::unique_ptr<PlatformFactory> instance = nullptr;

    inline PlatformFactory& Platform() {
        if (instance.get() == nullptr) {
            instance = std::make_unique<linux::LinuxFactory>();
        }
        return *instance;
    }
}

#endif

#if (CURRENT_PLATFORM == PLATFORM_WINDOWS)

#include <game/platform/windows/windows_factory.h>

namespace punkyoi::platform {

    static std::unique_ptr<PlatformFactory> instance = nullptr;

    inline PlatformFactory& Platform() {
        if (instance.get() == nullptr) {
            instance = std::make_unique<windows::WindowsFactory>();
        }
        return *instance;
    }
}

#endif
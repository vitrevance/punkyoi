#ifndef P_CORE
#define P_CORE

#include <string>
#include <memory>
#include <vector>
#include <api/utils/logger.h>

namespace punkyoi {
    using punkyoi_api::log;
}

#define PLATFORM_LINUX 0
#define PLATFORM_WINDOWS 1

namespace punkyoi_api::platform {
    enum class PlatformType {
        Linux = PLATFORM_LINUX,
        Windows = PLATFORM_WINDOWS
    };
}

#ifdef __linux
static constexpr punkyoi_api::platform::PlatformType currentPlatform = punkyoi_api::platform::PlatformType::Linux;
#define CURRENT_PLATFORM PLATFORM_LINUX
#elif defined(WIN32)
static constexpr Platform currentPlatform = Platform::Windows;
#define CURRENT_PLATFORM PLATFORM_WINDOWS
#endif

#endif

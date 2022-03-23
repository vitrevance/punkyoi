#ifndef P_CORE
#define P_CORE

#include <string>
#include <memory>
#include <vector>
#include <api/utils/logger.h>
#include <api/vec2d.h>
#include <api/matrix.h>
#include <api/object.h>

namespace punkyoi {
    using punkyoi_api::log;
    using punkyoi_api::vec2;
    using mat2 = punkyoi_api::mat<2, 2>;
    using mat3 = punkyoi_api::mat<3, 3>;
    using mat4 = punkyoi_api::mat<4, 4>;
    using punkyoi_api::object;
    using punkyoi_api::new_instance;
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

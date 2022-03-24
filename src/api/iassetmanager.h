#ifndef P_IASSETMANAGER
#define P_IASSETMANAGER

#include <string>

namespace punkyoi_api {

    class IAsset {
    public:
        virtual ~IAsset() = default;
        uint32_t uid;
    };

    class IAssetManager {
    public:
        virtual ~IAssetManager() = default;

        virtual void loadAssetMap(const std::string&) = 0;
        virtual IAsset& getAsset(const std::string&) = 0;
    };
}

#endif
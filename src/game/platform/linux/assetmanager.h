#ifndef P_PLATFORM_ASSETMANAGER
#define P_PLATFORM_ASSETMANAGER

#include <game/core.h>
#include <game/common/assetmanager.h>
#include <unordered_map>
#include <game/common/exception.h>
#include <fstream>
#include <tao/json.hpp>

namespace punkyoi::platform::linux {

    class PlatformAssetManager : public ::punkyoi::common::AssetManager {
    public:
        PlatformAssetManager();
        virtual ~PlatformAssetManager();

        virtual void loadAssetMap(const std::string&) override;
        virtual const ::punkyoi_api::IAsset& getAsset(const std::string&) override;
        virtual const ::punkyoi::common::ImageAsset& getImage(const std::string&) override;

    protected:
        std::unordered_map<std::string, ::punkyoi_api::IAsset*> m_assetMap;
    };
}

#endif
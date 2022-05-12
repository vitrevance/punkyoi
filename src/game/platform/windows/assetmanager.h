#ifndef P_PLATFORM_ASSETMANAGER
#define P_PLATFORM_ASSETMANAGER

#include <game/core.h>
#include <game/common/assetmanager.h>
#include <unordered_map>
#include <game/common/exception.h>
#include <fstream>
#include <tao/json.hpp>
#include <stb_image.h>

namespace punkyoi::platform::windows {

    class PlatformAssetManager : public ::punkyoi::common::AssetManager {
    public:
        PlatformAssetManager();
        virtual ~PlatformAssetManager();

        virtual void loadAssetMap(const ::std::string&) override;
        virtual ::punkyoi_api::IAsset& getAsset(const ::std::string&) override;
        virtual ::punkyoi::common::ImageAsset& getImage(const ::std::string&) override;
        virtual ::punkyoi::common::SoundAsset& getSound(const std::string&) override;

    protected:
        void processJson(const ::std::string& prefix, const ::tao::json::value& json);

        ::std::unordered_map<::std::string, ::punkyoi_api::IAsset*> m_assetMap;
        ::std::string m_root;
    };

    struct SpriteLoader {
        static ::punkyoi::common::ImageAsset* load(const ::std::string&);
    };

    struct SoundLoader {
        static ::punkyoi::common::SoundAsset* load(const std::string&);
    };
}

#endif
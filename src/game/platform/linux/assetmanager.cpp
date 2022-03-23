#include <game/core.h>

#if (CURRENT_PLATFORM == PLATFORM_LINUX)

#include "assetmanager.h"

namespace punkyoi::platform::linux {

    PlatformAssetManager::PlatformAssetManager() {
    }

    PlatformAssetManager::~PlatformAssetManager() {
        for (auto& it : m_assetMap) {
            delete it.second;
        }
    }

    void PlatformAssetManager::loadAssetMap(const std::string& filename) {
        std::ifstream reader(filename);
        std::stringstream contents;

        std::streampos p = reader.tellg();
        contents << reader.rdbuf(); 
        reader.seekg(p);

        reader.close();


        tao::json::value json = contents.str();
    }

    const ::punkyoi_api::IAsset& PlatformAssetManager::getAsset(const std::string& key) {
        if (!m_assetMap.count(key)) {
            throw ::punkyoi::common::exceptions::NoAssetException(key);
        }
    }

    const ::punkyoi::common::ImageAsset& PlatformAssetManager::getImage(const std::string&) {

    }
}

#endif
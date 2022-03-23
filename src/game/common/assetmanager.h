#ifndef P_ASSETMANAGER
#define P_ASSETMANAGER

#include <game/core.h>
#include <api/iassetmanager.h>
#include <api/iimage.h>

namespace punkyoi::common {

    class ImageAsset : public ::punkyoi_api::IAsset, ::punkyoi_api::IImage {
    public:
        virtual ~ImageAsset();
        virtual uint8_t* getBuffer() override;

    private:
        uint8_t* m_buffer = nullptr;
    };

    class AssetManager : public ::punkyoi_api::IAssetManager {
    public:
        virtual ~AssetManager() = default;
        virtual const ImageAsset& getImage(const std::string&) = 0;
        
    };
}

#endif
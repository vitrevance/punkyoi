#ifndef P_ASSETMANAGER
#define P_ASSETMANAGER

#include <game/core.h>
#include <api/iassetmanager.h>
#include <api/iimage.h>
#include <api/isound.h>

namespace punkyoi::common {

    class ImageAsset : public ::punkyoi_api::IAsset, public ::punkyoi_api::IImage {
    public:
        ImageAsset(int width, int height, uint8_t* buffer);
        virtual ~ImageAsset();
        virtual uint8_t* getBuffer() override;
        virtual int getWidth() override;
        virtual int getHeight() override;

    private:
        uint8_t* m_buffer = nullptr;
        int m_width = 0;
        int m_height = 0;
    };

    class SoundAsset : public ::punkyoi_api::IAsset, public ::punkyoi_api::ISound {
    public:
        SoundAsset(const std::string& path);
        virtual ~SoundAsset() = default;
        virtual void* getBuffer() override;
        virtual const std::string& source() const override;
    protected:
        std::string m_source;
    };

    class AssetManager : public ::punkyoi_api::IAssetManager {
    public:
        virtual ~AssetManager() = default;
        virtual ImageAsset& getImage(const std::string&) = 0;
        virtual SoundAsset& getSound(const std::string&) = 0;
        
    };
}

#endif
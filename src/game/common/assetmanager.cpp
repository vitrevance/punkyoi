#include "assetmanager.h"

namespace punkyoi::common {

    ImageAsset::ImageAsset(int width, int height, uint8_t* buffer)
        : m_width(width), m_height(height), m_buffer(buffer) {}

    ImageAsset::~ImageAsset() {
        delete[] m_buffer;
    }

    uint8_t* ImageAsset::getBuffer() {
        return m_buffer;
    }

    int ImageAsset::getWidth() {
        return m_width;
    }

    int ImageAsset::getHeight() {
        return m_height;
    }

    SoundAsset::SoundAsset(const std::string& path) : m_source(path) {
    }

    const std::string& SoundAsset::source() const {
        return m_source;
    }

    void* SoundAsset::getBuffer() {
        return nullptr;
    }
}
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
}
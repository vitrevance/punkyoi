#include "assetmanager.h"

namespace punkyoi::common {

    ImageAsset::~ImageAsset() {
        delete[] m_buffer;
    }

    uint8_t* ImageAsset::getBuffer() {
        return m_buffer;
    }
}
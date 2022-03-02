#pragma once

#include <stdint.h>
#include <vector>

namespace punkyoi_api {

    class Message {
    public:
        struct Header {
            uint32_t id = 0;
            uint32_t size = 0;
        } header;
        
        std::vector<uint8_t> body;
    };
}
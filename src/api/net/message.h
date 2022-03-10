#pragma once

#include <stdint.h>
#include <vector>

namespace punkyoi_api::net {

    class Message {
    public:
        struct Header {
            Header() {}
            Header(uint32_t id, uint32_t size) : id(id), size(size) {}

            uint32_t id = 0;
            uint32_t size = 0;
        };

        Message() {}
        
        Message(uint32_t id, const std::vector<uint8_t>& bytes) : header(Header(id, bytes.size())), body(bytes) {}
        Message(const Header& header) : header(header) {}
        Message(const Header& header, const std::vector<uint8_t>& body) : header(header), body(body) {}

        Header header;
        std::vector<uint8_t> body;
    };

    template<typename owner>
    struct OwnedMessage {
        std::shared_ptr<owner> remote = nullptr;
        Message message;
    };
}
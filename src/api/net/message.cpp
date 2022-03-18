#include "message.h"

namespace punkyoi_api::net {

    Message::Message() {}
    
    Message::Message(uint32_t id, const std::vector<uint8_t>& bytes) : header(Header(id, bytes.size())), body(bytes) {}
    Message::Message(const Header& header) : header(header) {}
    Message::Message(const Header& header, const std::vector<uint8_t>& body) : header(header), body(body) {}
}
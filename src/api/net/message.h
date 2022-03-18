#ifndef P_MESSAGE
#define P_MESSAGE

#include <stdint.h>
#include <vector>
#include <memory>

namespace punkyoi_api::net {

    class Message {
    public:
        struct Header {
            Header() {}
            Header(uint32_t id, uint32_t size) : id(id), size(size) {}

            uint32_t id = 0;
            uint32_t size = 0;
        };

        Message();
        
        Message(uint32_t id, const std::vector<uint8_t>& bytes);
        Message(const Header& header);
        Message(const Header& header, const std::vector<uint8_t>& body);

        Header header;
        std::vector<uint8_t> body;
    };

    template<typename owner>
    struct OwnedMessage {
        std::shared_ptr<owner> remote = nullptr;
        Message message;
    };
}

#endif

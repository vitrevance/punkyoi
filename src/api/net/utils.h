#ifndef P_UTILS
#define P_UTILS

#include <asio.hpp>
#include <string>

namespace punkyoi_api::net {
    struct utils {
        struct EndpointBuilder {
            EndpointBuilder(asio::io_context& context) : m_context(context) {}

            EndpointBuilder& from(asio::ip::tcp::endpoint endpoint) {
                address = endpoint.address().to_string();
                port = endpoint.port();
                return *this;
            }

            EndpointBuilder& from(asio::ip::udp::endpoint endpoint) {
                address = endpoint.address().to_string();
                port = endpoint.port();
                return *this;
            }

            EndpointBuilder& setAddress(const std::string& value) {
                address = address;
                return *this;
            }

            EndpointBuilder& setPort(uint16_t value) {
                port = value;
                return *this;
            }

            asio::ip::tcp::endpoint buildTCP() {
                asio::ip::tcp::resolver resolver(m_context);
                auto result = resolver.resolve(address, std::to_string(port));
                return *result;
            }

            asio::ip::udp::endpoint buildUDP() {
                asio::ip::udp::resolver resolver(m_context);
                auto result = resolver.resolve(address, std::to_string(port));
                return *result;
            }

            std::string address;
            uint16_t port;
        private:
            asio::io_context& m_context;
        };
    };
}

#endif

#pragma once

#include "asio.hpp"
#include "tsqueue.h"
#include "message.h"
#include "connection.h"
#include <memory>
#include <string>
#include <api/utils/logger.h>
#include "utils.h"

namespace punkyoi_api::net {

    class Client {
    public:
        Client() {
        }

        ~Client() {
            disconnect();
        }

        bool connect(const std::string& host, const uint16_t port) {
            try {
                m_TCPconnection = std::make_unique<TCPConnection>(TCPConnection::Owner::CLIENT, m_context, asio::ip::tcp::socket(m_context), m_inMessagesTCP);                    

                asio::ip::tcp::resolver tcpResolver(m_context);
                asio::ip::tcp::resolver::results_type tcpEndpoints = tcpResolver.resolve(host, std::to_string(port));

                m_TCPconnection->connectToServer(tcpEndpoints);

                m_thread = std::thread([this]() { m_context.run(); });
                return true;
            }
            catch (const std::exception& e) {
                std::cerr << "Client connection exception: " << e.what() << std::endl;
                if (m_TCPconnection) {
                    m_TCPconnection->disconnect();
                    m_TCPconnection.release();
                }
            }
            return false;
        }

        void disconnect() {
            if (m_TCPconnection) {
                m_TCPconnection->disconnect();
            }

            m_context.stop();
            if (m_thread.joinable()) {
                m_thread.join();
            }
            m_TCPconnection.release();
        }

        bool isConnected() {
            if (m_TCPconnection) {
                return m_TCPconnection->isConnected();
            }
            return false;
        }

        void sendTCP(const Message& message) {
            if (isConnected()) {
                m_TCPconnection->send(message);
            }
        }

        tsqueue<OwnedMessage<TCPConnection> >& TCPIncome() {
            return m_inMessagesTCP;
        }

    protected:
        asio::io_context m_context;
        std::unique_ptr<TCPConnection> m_TCPconnection;

        std::thread m_thread;
        tsqueue<OwnedMessage<TCPConnection> > m_inMessagesTCP;
    };
}
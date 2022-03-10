#pragma once

#include "asio.hpp"
#include "tsqueue.h"
#include "message.h"
#include "connection.h"
#include <memory>
#include <string>
#include <iostream>

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
                m_UDPconnection = std::make_unique<UDPConnection>(UDPConnection::Owner::CLIENT, m_context, asio::ip::udp::socket(m_context), m_inMessagesUDP);

                asio::ip::tcp::resolver tcpResolver(m_context);
                asio::ip::udp::resolver udpResolver(m_context);
                asio::ip::tcp::resolver::results_type tcpEndpoints = tcpResolver.resolve(host, std::to_string(port));
                asio::ip::udp::resolver::results_type udpEndpoints = udpResolver.resolve(host, std::to_string(port));

                m_TCPconnection->connectToServer(tcpEndpoints);
                m_UDPconnection->connectToServer(udpEndpoints);

                m_thread = std::thread([this]() { m_context.run(); });
                return true;
            }
            catch (const std::exception& e) {
                std::cerr << "Client connection exception: " << e.what() << '\n';
                if (m_TCPconnection) {
                    m_TCPconnection->disconnect();
                    m_TCPconnection.release();
                }
                if (m_UDPconnection) {
                    m_UDPconnection->disconnect();
                    m_UDPconnection.release();
                }
            }
            return false;
        }

        void disconnect() {
            if (m_TCPconnection) {
                m_TCPconnection->disconnect();
            }
            if (m_UDPconnection) {
                m_UDPconnection->disconnect();
            }

            m_context.stop();
            if (m_thread.joinable()) {
                m_thread.join();
            }
            m_TCPconnection.release();
            m_UDPconnection.release();
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

        void sendUDP(const Message& message) {
            if (isConnected()) {
                m_UDPconnection->send(message);
            }
        }

        tsqueue<OwnedMessage<TCPConnection> >& TCPIncome() {
            return m_inMessagesTCP;
        }

        tsqueue<OwnedMessage<UDPConnection> >& UDPIncome() {
            return m_inMessagesUDP;
        }

    protected:
        asio::io_context m_context;
        std::unique_ptr<TCPConnection> m_TCPconnection;
        std::unique_ptr<UDPConnection> m_UDPconnection;

        std::thread m_thread;
        tsqueue<OwnedMessage<TCPConnection> > m_inMessagesTCP;
        tsqueue<OwnedMessage<UDPConnection> > m_inMessagesUDP;
    };
}
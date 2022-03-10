#pragma once

#include "asio.hpp"
#include <thread>
#include <memory>
#include <deque>
#include <iostream>
#include "connection.h"

namespace punkyoi_api::net {

    class Server {
    public:
        Server(uint16_t port)
            : m_TCPAcceptor(m_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)),
              m_UDPEndpoint(asio::ip::udp::v4(), port) {
        }

        ~Server() {
            stop();
        }

        bool start() {
            try {
                waitForClientConnection();

                m_thread = std::thread([this]() { m_context.run(); });
            }
            catch (const std::exception& e) {
                std::cerr << "Server start error: " << e.what() << '\n';
                return false;
            }

            std::cout << "Server started on port " << m_UDPEndpoint.port() << '\n';
            return true;
        }

        void stop() {
            m_context.stop();
            if (m_thread.joinable()) {
                m_thread.join();
            }
            std::cout << "Server stopped!\n";
        }

    protected:
        virtual bool onClientConnect(std::shared_ptr<TCPConnection> connection) {
            return true;
        }

    private:
        void waitForClientConnection() {
            m_TCPAcceptor.async_accept(
                [this](std::error_code ec, asio::ip::tcp::socket socket) {
                    if (ec) {
                        std::cout << "Server connection error: " << ec.message() << '\n';
                    }
                    else {
                        std::cout << "Server new connection from remote: " << socket.remote_endpoint().address() << ":" << socket.remote_endpoint().port() << '\n';
                        std::shared_ptr<TCPConnection> connection = std::make_shared<TCPConnection>(TCPConnection::Owner::SERVER, m_context, std::move(socket), m_inMessagesTCP);

                        if (onClientConnect(connection)) {
                            m_TCPConnections.push_back(std::move(connection));
                            m_TCPConnections.back()->connectToClient(m_nextID++);
                        }
                        else {
                            std::cout << "Server: connection denied.\n";
                        }
                    }

                    waitForClientConnection();
                }
            );
        }

    public:
        asio::io_context m_context;
        asio::ip::tcp::acceptor m_TCPAcceptor;
        asio::ip::udp::endpoint m_UDPEndpoint;
        std::thread m_thread;

        std::deque<std::shared_ptr<TCPConnection> > m_TCPConnections;
        std::deque<std::shared_ptr<UDPConnection> > m_UDPConnections;

        tsqueue<OwnedMessage<TCPConnection> > m_inMessagesTCP;
        tsqueue<OwnedMessage<UDPConnection> > m_inMessagesUDP;

        uint32_t m_nextID;
    };
}
#pragma once

#include "asio.hpp"
#include <thread>
#include <memory>
#include <deque>
#include "connection.h"
#include <iostream>
#include <api/utils/logger.h>

namespace punkyoi_api::net {

    class Server {
    public:
        Server(uint16_t port)
            : m_TCPAcceptor(m_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)) {
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
                std::cerr << "Server start error: " << e.what() << std::endl;
                return false;
            }

            punkyoi_api::log::console() << "Server started on port " << m_TCPAcceptor.local_endpoint().port() << punkyoi_api::log::endl;
            return true;
        }

        void stop() {
            m_context.stop();
            if (m_thread.joinable()) {
                m_thread.join();
            }
            punkyoi_api::log::console() << "Server stopped!" << punkyoi_api::log::endl;
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
                        punkyoi_api::log::console() << "Server connection error: " << ec.message() << punkyoi_api::log::endl;
                    }
                    else {
                        punkyoi_api::log::console() << "Server new connection from remote: " << socket.remote_endpoint() << punkyoi_api::log::endl;
                        std::shared_ptr<TCPConnection> connection = std::make_shared<TCPConnection>(TCPConnection::Owner::SERVER, m_context, std::move(socket), m_inMessagesTCP);
                        if (onClientConnect(connection)) {
                            uint32_t clientID = m_nextID++;
                            m_TCPConnections.push_back(std::move(connection));
                            m_TCPConnections.back()->connectToClient(clientID);
                        }
                        else {
                            punkyoi_api::log::console() << "Server: connection denied." << punkyoi_api::log::endl;
                        }
                    }

                    waitForClientConnection();
                }
            );
        }

    public:
        asio::io_context m_context;
        asio::ip::tcp::acceptor m_TCPAcceptor;
        std::thread m_thread;

        std::deque<std::shared_ptr<TCPConnection> > m_TCPConnections;
        tsqueue<OwnedMessage<TCPConnection> > m_inMessagesTCP;

        uint32_t m_nextID;
    };
}
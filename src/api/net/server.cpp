#include "server.h"

namespace punkyoi_api::net {

    Server::Server(uint16_t port)
        : m_TCPAcceptor(m_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)) {
    }

    Server::~Server() {
        stop();
    }

    bool Server::start() {
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

    void Server::stop() {
        m_context.stop();
        if (m_thread.joinable()) {
            m_thread.join();
        }
        punkyoi_api::log::console() << "Server stopped!" << punkyoi_api::log::endl;
    }

    bool Server::onClientConnect(std::shared_ptr<TCPConnection> connection) {
        return true;
    }

    void Server::waitForClientConnection() {
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
}
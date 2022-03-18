#include "client.h"

namespace punkyoi_api::net {

    Client::Client() {
    }

    Client::~Client() {
        disconnect();
    }

    bool Client::connect(const std::string& host, const uint16_t port) {
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

    void Client::disconnect() {
        if (m_TCPconnection) {
            m_TCPconnection->disconnect();
        }

        m_context.stop();
        if (m_thread.joinable()) {
            m_thread.join();
        }
        m_TCPconnection.release();
    }

    bool Client::isConnected() {
        if (m_TCPconnection) {
            return m_TCPconnection->isConnected();
        }
        return false;
    }

    void Client::sendTCP(const Message& message) {
        if (isConnected()) {
            m_TCPconnection->send(message);
        }
    }

    tsqueue<OwnedMessage<TCPConnection> >& Client::TCPIncome() {
        return m_inMessagesTCP;
    }
}
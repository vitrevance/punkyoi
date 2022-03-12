#pragma once

#include <asio.hpp>
#include <asio/ip/tcp.hpp>
#include <asio/ip/udp.hpp>
#include <memory>
#include <api/utils/logger.h>

#include "tsqueue.h"
#include "message.h"

namespace punkyoi_api::net {

    template<typename interface>
    class Connection : public std::enable_shared_from_this<Connection<interface> > {
    public:

        enum class Owner {
            CLIENT, SERVER
        };

        Connection(Owner owner, asio::io_context& context, typename interface::socket socket, tsqueue<OwnedMessage<Connection> >& qIn)
            : m_owner(owner), m_context(context), m_socket(std::move(socket)), m_inMessages(qIn) {
        }

        ~Connection() {
            disconnect();
        }

        void connectToClient(uint32_t id) {
            if (m_owner == Owner::SERVER) {
                if (m_socket.is_open()) {
                    m_id = id;
                    m_remote_endpoint = m_socket.remote_endpoint();
                    readHeader();
                }
            }
        }

        void connectToServer(const typename interface::resolver::results_type& endpoints) {
            if (m_owner == Owner::CLIENT) {
                m_remote_endpoint = *endpoints;
                asio::async_connect(m_socket, endpoints,
                    [this](std::error_code ec, typename interface::endpoint endpoint) {
                        if (!ec) {
                            readHeader();
                        }
                    }
                );
            }
        }

        void connectToServer(const typename interface::endpoint& endpoint) {
            if (m_owner == Owner::CLIENT) {
                m_remote_endpoint = endpoint;
                m_socket.async_connect(endpoint,
                    [this](std::error_code ec) {
                        if (!ec) {
                            readHeader();
                        }
                    }
                );
            }
        }

        void disconnect() {
            asio::post(m_context, [this]() { m_socket.close(); });
        }

        bool isConnected() {
            return m_socket.is_open();
        }

        void send(const Message& message) {
            asio::post(m_context, 
                [this, message]() {
                    bool shouldWrite = m_outMessages.empty();
                    m_outMessages.push_back(message);
                    if (shouldWrite) {
                        writeHeader();
                    }
                }
            );
        }

        uint32_t getID() const {
            return m_id;
        }

        typename interface::socket& getSocket() {
            return m_socket;
        }

    protected:
        void readHeader();
        void readBody();
        void writeHeader();
        void writeBody();

        void addToIncomeQueue() {
            if (m_owner == Owner::SERVER) {
                m_inMessages.push_back(OwnedMessage<Connection>{this->shared_from_this(), m_inMessageDirty});
            }
            else {
                m_inMessages.push_back(OwnedMessage<Connection>{nullptr, m_inMessageDirty});
            }
            readHeader();
        }

        Owner m_owner;
        uint32_t m_id;
        typename interface::socket m_socket;
        typename interface::endpoint m_remote_endpoint;
        asio::io_context& m_context;
        tsqueue<Message> m_outMessages;
        tsqueue<OwnedMessage<Connection> >& m_inMessages;

        Message m_inMessageDirty;
    };

    using TCPConnection = Connection<asio::ip::tcp>;

    template<>
    void TCPConnection::readBody() {
        asio::async_read(m_socket, asio::buffer(m_inMessageDirty.body.data(), m_inMessageDirty.body.size()),
            [this](std::error_code ec, std::size_t length) {
                if (ec) {
                    punkyoi_api::log::console() << "[" << m_id << "] read body fail" << punkyoi_api::log::endl;
                    m_socket.close();
                }
                else {
                    addToIncomeQueue();
                }
            }
        );
    }

    template<>
    void TCPConnection::readHeader() {
        asio::async_read(m_socket, asio::buffer(&m_inMessageDirty.header, sizeof(Message::Header)),
            [this](std::error_code ec, std::size_t length) {
                if (ec) {
                    punkyoi_api::log::console() << "[" << m_id << "] read header fail" << punkyoi_api::log::endl;
                    m_socket.close();
                }
                else {
                    if (m_inMessageDirty.header.size > 0) {
                        m_inMessageDirty.body.resize(m_inMessageDirty.header.size);
                        readBody();
                    }
                    else {
                        addToIncomeQueue();
                    }
                }
            }
        );
    }

    template<>
    void TCPConnection::writeHeader();

    template<>
    void TCPConnection::writeBody();

    template<>
    void TCPConnection::writeHeader() {
        asio::async_write(m_socket, asio::buffer(&m_outMessages.front().header, sizeof(Message::Header)),
            [this](std::error_code ec, std::size_t length) {
                if (!ec) {
                    if (m_outMessages.front().header.size > 0) {
                        writeBody();
                    }
                    else {
                        m_outMessages.pop_front();
                        if (!m_outMessages.empty()) {
                            writeHeader();
                        }
                    }
                }
            }
        );
    }

    template<>
    void TCPConnection::writeBody() {
        asio::async_write(m_socket, asio::buffer(m_outMessages.front().body.data(), m_outMessages.front().body.size()),
            [this](std::error_code ec, std::size_t length) {
                if (!ec) {
                    m_outMessages.pop_front();
                    if (!m_outMessages.empty()) {
                        writeHeader();
                    }
                }
            }
        );
    }
}
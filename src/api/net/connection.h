#pragma once

#include <asio.hpp>
#include <asio/ip/tcp.hpp>
#include <memory>

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
                    readHeader();
                }
            }
        }

        void connectToServer(const typename interface::resolver::results_type& endpoints) {
            if (m_owner == Owner::CLIENT) {
                m_sender_endpoint = *endpoints;
                asio::async_connect(m_socket, endpoints,
                    [this](std::error_code ec, typename interface::endpoint endpoint) {
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
        typename interface::endpoint m_sender_endpoint;
        asio::io_context& m_context;
        tsqueue<Message> m_outMessages;
        tsqueue<OwnedMessage<Connection> >& m_inMessages;

        Message m_inMessageDirty;
    };

    using TCPConnection = Connection<asio::ip::tcp>;
    using UDPConnection = Connection<asio::ip::udp>;

    template<>
    void TCPConnection::readBody() {
        asio::async_read(m_socket, asio::buffer(m_inMessageDirty.body.data(), m_inMessageDirty.body.size()),
            [this](std::error_code ec, std::size_t length) {
                if (ec) {
                    std::cout << "[" << m_id << "] read body fail\n";
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
                    std::cout << "[" << m_id << "] read header fail\n";
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
    void UDPConnection::readBody() {
        m_socket.async_receive_from(asio::buffer(m_inMessageDirty.body.data(), m_inMessageDirty.body.size()), m_sender_endpoint,
            [this](std::error_code ec, std::size_t length) {
                if (ec) {
                    std::cout << "[" << m_id << "] read body fail\n";
                    m_socket.close();
                }
                else {
                    addToIncomeQueue();
                }
            }
        );
    }

    template<>
    void UDPConnection::readHeader() {
        m_socket.async_receive_from(asio::buffer(&m_inMessageDirty.header, sizeof(Message::Header)), m_sender_endpoint,
            [this](std::error_code ec, std::size_t length) {
                if (ec) {
                    std::cout << "[" << m_id << "] read header fail\n";
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

    template<>
    void UDPConnection::writeHeader();

    template<>
    void UDPConnection::writeBody();

    template<>
    void UDPConnection::writeHeader() {
        m_socket.async_send_to(asio::buffer(&m_outMessages.front().header, sizeof(Message::Header)), m_sender_endpoint,
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
    void UDPConnection::writeBody() {
        m_socket.async_send_to(asio::buffer(m_outMessages.front().body.data(), m_outMessages.front().body.size()), m_sender_endpoint,
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
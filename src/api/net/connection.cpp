#include "connection.h"

namespace punkyoi_api::net {

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
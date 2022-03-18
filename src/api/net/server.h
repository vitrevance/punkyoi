#ifndef P_SERVER
#define P_SERVER

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
        Server(uint16_t port);
        ~Server();

        bool start();
        void stop();

    protected:
        virtual bool onClientConnect(std::shared_ptr<TCPConnection> connection);
        void waitForClientConnection();
        
        asio::io_context m_context;
        asio::ip::tcp::acceptor m_TCPAcceptor;
        std::thread m_thread;

        std::deque<std::shared_ptr<TCPConnection> > m_TCPConnections;
        tsqueue<OwnedMessage<TCPConnection> > m_inMessagesTCP;

        uint32_t m_nextID;
    };
}

#endif

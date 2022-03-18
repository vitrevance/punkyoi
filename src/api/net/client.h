#ifndef P_CLIENT
#define P_CLIENT

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
        Client();

        ~Client();

        bool connect(const std::string& host, const uint16_t port);

        void disconnect();

        bool isConnected();

        void sendTCP(const Message& message);

        tsqueue<OwnedMessage<TCPConnection> >& TCPIncome();

    protected:
        asio::io_context m_context;
        std::unique_ptr<TCPConnection> m_TCPconnection;

        std::thread m_thread;
        tsqueue<OwnedMessage<TCPConnection> > m_inMessagesTCP;
    };
}

#endif

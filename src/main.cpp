#include <iostream>

#include <api/net/server.h>
#include <api/net/client.h>

#include <iostream>
#include <string>

int main() {
    std::cout << "Hello from app" << std::endl;
    punkyoi_api::net::Server server(25565);
    server.start();
    punkyoi_api::net::Client client;
    std::string msg;
    std::cin >> msg;
    bool res = client.connect("127.0.0.1", 25565);
    if (res) {
        std::cout << "Connected" << std::endl;
    }
    for (char c = 0; c != 'y' && c != 'n';) {
        std::cout << std::endl << "Procceed? [y/n]\n";
        std::cin >> c;
        if (c == 'y') {
            punkyoi_api::net::Message msg(123, {1, 2, 3, 4, 5});
            client.sendTCP(msg);
            client.sendUDP(msg);
        }
    }
    while (true) {
        if (!server.m_inMessagesTCP.empty()) {
            auto msg = server.m_inMessagesTCP.front();
            server.m_inMessagesTCP.pop_front();
            std::cout << ">t " << msg.message.header.id << " " << msg.message.header.size << std::endl;
            break;
        }
        if (!server.m_inMessagesUDP.empty()) {
            auto msg = server.m_inMessagesTCP.front();
            server.m_inMessagesTCP.pop_front();
            std::cout << ">u " << msg.message.header.id << " " << msg.message.header.size << std::endl;
            break;
        }
    }
    client.disconnect();
    return 0;
}

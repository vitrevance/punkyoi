#include <iostream>

#include <api/net/server.h>
#include <api/net/client.h>

#include <iostream>
#include <string>

int main() {
    std::cout << "Hello from app\nServer port:" << std::endl;
    uint16_t prefered_server;
    std::cin >> prefered_server;
    punkyoi_api::net::Server server(prefered_server);
    server.start();
    punkyoi_api::net::Client client;
    std::string usr;
    std::cin >> usr;
    bool res = client.connect("127.0.0.1", prefered_server);
    if (res) {
        std::cout << "Connected" << std::endl;
    }
    punkyoi_api::net::Message msg({123, 0});
    for (char c = 0; c != 'y' && c != 'n';) {
        std::cout << std::endl << "Procceed? [y/n]\n";
        std::cin >> c;
        if (c == 'y') {
            client.sendTCP(msg);
            //client.sendUDP(msg);
        }
        if (c == 'n') {
            client.disconnect();
            server.stop();
            return 0;
        }
    }
    while (true) {
        if (!server.m_inMessagesTCP.empty()) {
            auto msg = server.m_inMessagesTCP.front();
            server.m_inMessagesTCP.pop_front();
            std::cout << ">t " << msg.message.header.id << " " << msg.message.header.size << std::endl;
            //break;
        }
        if (!server.m_inMessagesUDP.empty()) {
            auto msg = server.m_inMessagesTCP.front();
            server.m_inMessagesTCP.pop_front();
            std::cout << ">u " << msg.message.header.id << " " << msg.message.header.size << std::endl;
            //break;
        }
        std::cout << "Send test request? [y/n]" << std::endl;
        std::cin >> usr;
        if (usr == "y") {
            client.sendUDP(msg);
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
        if (usr == "n") {
            break;
        }
    }
    client.disconnect();
    return 0;
}

#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <stdexcept>
#include <vector>

class Client {
public:
    Client(const std::string& serverIp, int serverPort);
    ~Client();

    bool connectToServer();
    bool sendMessage(std::string message);
    bool sendMessage(std::vector<std::string> message);
    std::vector<std::string> receiveMessage();

private:
    int clientSocket;
    std::string serverIp;
    int serverPort;
};

#endif // CLIENT_H

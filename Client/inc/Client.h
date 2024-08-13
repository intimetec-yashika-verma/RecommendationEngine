#pragma once
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <stdexcept>
#include <vector>

class Client
{
public:
    Client(const std::string &serverIp, int serverPort);
    ~Client();

    bool connectToServer();
    bool sendMessage(std::string message);
    std::string receiveMessage();
    void disconnect();

private:
    int clientSocket;
    std::string serverIp;
    int serverPort;
};



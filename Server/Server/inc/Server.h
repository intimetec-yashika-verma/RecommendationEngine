#pragma once

#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <vector>
#include <thread>
#include "DatabaseConnection.h"

class Server
{
public:
    Server(int port);
    ~Server();

    void startListening();
    void stop();

private:
    int serverSocket;
    int clientSocket;
    struct sockaddr_in serverAddr;
    struct sockaddr_in clientAddr;
    socklen_t clientAddrLen;
    int port;
    std::vector<std::thread> clientThreads;
    std::vector<int> clientSockets;
};

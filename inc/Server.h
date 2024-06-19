#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <vector>
#include <thread>

class Server {
public:
    Server(int port);
    ~Server();

    void startListening();
    static  std::vector<std::string> receiveMessage(int clientSocket);
    static void sendMessage(std::vector<std::string> message,int clientSocket);
    void createSession(std::string reponse);

private:
    int serverSocket;
    int clientSocket;
    struct sockaddr_in serverAddr;
    struct sockaddr_in clientAddr;
    socklen_t clientAddrLen;
    int port;
    std::vector<std::thread> clientThreads;
    void handleClient(int clientSocket);
};

#endif // SERVER_H

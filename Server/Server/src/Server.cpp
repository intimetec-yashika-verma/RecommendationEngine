#include "Server.h"
#include <thread>
#include <mutex>
#include "ClientHandler.h"

#include "DatabaseConnection.h"

Server::Server(int port) : port(port)
{
    // Create a socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1)
    {
        std::cerr << "Failed to create socket." << std::endl;
        throw std::runtime_error("Failed to create socket.");
    }

    // Prepare the sockaddr_in structure
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    // Bind
    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1)
    {
        std::cerr << "Bind failed. Error: " << strerror(errno) << std::endl;
        close(serverSocket);
        throw std::runtime_error("Bind failed.");
    }

    // Listen
    if (listen(serverSocket, 5) == -1)
    {
        std::cerr << "Listen failed. Error: " << strerror(errno) << std::endl;
        close(serverSocket);
        throw std::runtime_error("Listen failed.");
    }

    std::cout << "Server listening on port " << port << "..." << std::endl;
}

Server::~Server()
{
    close(serverSocket);
}

void Server::startListening()
{

    while (true)
    {
        struct sockaddr_in clientAddr;
        socklen_t clientAddrSize = sizeof(clientAddr);
        int clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &clientAddrSize);
        if (clientSocket < 0)
        {
            std::cerr << "Accept failed" << std::endl;
            continue;
        }

        std::thread clientThread(&ClientHandler::handle, ClientHandler(clientSocket));
        clientThreads.push_back(std::move(clientThread));
        clientSockets.push_back(clientSocket);
    }
}

void Server::stop()
{

    for (int clientSocket : clientSockets)
    {
        send(clientSocket, "exit", strlen("exit"), 0);
        close(clientSocket);
    }

    clientSockets.clear();
    clientThreads.clear();

    std::cout << "Server stopped" << std::endl;
}

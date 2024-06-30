#include "Server.h"
#include <thread>
#include "ClientHandler.h"
#include "StringSerializer.h"
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
    // Accept incoming connections

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

        // Create a thread to handle this client
        
        std::thread clientThread(&ClientHandler::handle, ClientHandler(clientSocket));
        clientThreads.push_back(std::move(clientThread));
    }
}

std::vector<std::string> Server::receiveMessage()
{

    char buffer[1024];
    int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesRead == -1)
    {
        std::cerr << "Receive failed. Error: " << strerror(errno) << std::endl;
    }
    else if (bytesRead == 0)
    {
        std::cerr << "Connection closed by client." << std::endl;
    }
    else
    {
        buffer[bytesRead] = '\0';
        std::cout << "Client: " << buffer << std::endl;
    }
    std::string str(buffer);
    StringSerializer stringSerializer = StringSerializer();
    std::vector<std::string> receivedVector = stringSerializer.deserialize(str);
    return receivedVector;
}

bool Server::sendMessage(std::vector<std::string> message)
{
    StringSerializer stringSerializer = StringSerializer();
    std::string messageToSent = stringSerializer.serialize(message);
    // std::cout<<messageToSent<<std::endl;
    ssize_t bytesSent = send(clientSocket, messageToSent.c_str(), strlen(messageToSent.c_str()), 0);
    if (bytesSent == -1)
    {
        std::cerr << "Send failed. Error: " << strerror(errno) << std::endl;
    }
    else
    {
        std::cout << "Message sent to client." << std::endl;
    }
}

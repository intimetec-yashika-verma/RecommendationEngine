#include "ClientHandler.h"
#include "StringSerializer.h"
#include "RequestProcessor.h"

ClientHandler::ClientHandler(int clientSocket)
    : clientSocket(clientSocket), running(true)
{
}

void ClientHandler::handle()
{
    while (running)
    {
        std::string dataReceived = receiveRequest();
        if (dataReceived.size() == 0)
        {
            continue; // Continue to listen for further data
        }

        std::string response = requestProcessor.processRequest(dataReceived);
        if (!sendRequest(response))
        {
            std::cerr << "Failed to send response" << std::endl;
            break;
        }
    }

    // Closing the socket
    close(clientSocket);
}

bool ClientHandler::sendRequest(std::string response)
{
    // std::cout<<messageToSent<<std::endl;
    ssize_t bytesSent = send(clientSocket, response.c_str(), strlen(response.c_str()), 0);
    if (bytesSent == -1)
    {
        std::cerr << "Send failed. Error: " << strerror(errno) << std::endl;
    }
    else
    {
        std::cout << "Message sent to client." << std::endl;
    }
    return true;
}

std::string ClientHandler::receiveRequest()
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
    std::cout << "stirng response " << str << std::endl;

    return str;
}
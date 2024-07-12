#include "Client.h"
#include "StringSerializer.h"
#include <vector>

Client::Client(const std::string &serverIp, int serverPort)
    : serverIp(serverIp), serverPort(serverPort)
{
}

Client::~Client()
{
    if (clientSocket != -1)
    {
        close(clientSocket);
    }
}

bool Client::connectToServer()
{
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1)
    {
        std::cerr << "Failed to create socket." << std::endl;
        return false;
    }

    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(serverPort);
    if (inet_pton(AF_INET, serverIp.c_str(), &serverAddr.sin_addr) <= 0)
    {
        std::cerr << "Invalid address/ Address not supported." << std::endl;
        close(clientSocket);
        return false;
    }

    if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1)
    {
        std::cerr << "Connection failed." << std::endl;
        close(clientSocket);
        return false;
    }

    return true;
}
bool Client::sendMessage(std::string message)
{
    // std::cout<<messageToSent.c_str()<<std::endl;
    ssize_t bytesSent = send(clientSocket, message.c_str(), message.size(), 0);
    //std::cout<<bytesSent<<std::endl;
    if (bytesSent == -1)
    {
        std::cerr << "Send failed." << std::endl;
        return false;
    }
    return true;
}
bool Client::sendMessage(std::vector<std::string> message)
{

    StringSerializer stringSerializer = StringSerializer();
    std::string messageToSent = stringSerializer.serialize(message);
    std::cout<<"messageToSent:-"<<messageToSent<<std::endl;
    // std::cout<<messageToSent.c_str()<<std::endl;
    ssize_t bytesSent = send(clientSocket, messageToSent.c_str(), messageToSent.size(), 0);
    //std::cout<<bytesSent<<std::endl;
    if (bytesSent == -1)
    {
        std::cerr << "Send failed." << std::endl;
        return false;
    }
    return true;
}

std::string Client::receiveMessage()
{
    char buffer[1024];
    int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesRead == -1)
    {
        std::cerr << "Receive failed." << std::endl;
        
    }
    else if (bytesRead == 0)
    {
        std::cerr << "Connection closed by server." << std::endl;
        
    }
    else
    {
        buffer[bytesRead] = '\0';
        std::string str(buffer);
        return str;
    }
}

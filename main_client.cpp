#include "Client.h"
#include "ClientController.h"
#include <iostream>
#include <csignal>
Client *clientInstance = nullptr;
void clientHandlerWrapper(int signal)
{
    if (clientInstance)
    {
        clientInstance->disconnect();
    }
    exit(signal);
}
int main()
{
    try
    {
        std::string serverIp = "127.0.0.1";
        int serverPort;
        std::cin >> serverPort;
        Client *client = new Client(serverIp, serverPort);
        clientInstance = client;
        std::signal(SIGINT, clientHandlerWrapper);
        if (!client->connectToServer())
        {
            std::cerr << "Failed to connect to server." << std::endl;
            return 1;
        }
        ClientController clientController = ClientController(client);
        clientController.run();
    }
    catch (const char *msg)
    {
        std::cerr << msg << std::endl;
    }
    return 0;
}

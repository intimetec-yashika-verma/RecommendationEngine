#include <csignal>
#include "Server.h"
Server *serverInstance = nullptr;

void signalHandlerWrapper(int signal)
{
    if (serverInstance)
    {
        std::cout << "Signal " << signal << " received. Shutting down the server..." << std::endl;
        serverInstance->stop();
        std::cout << "Server stopped." << std::endl;
    }
    exit(signal);
}
int main()
{
    int port;
    std::cout << "Enter server port number: ";
    std::cin >> port;
    Server *server = new Server(port);
    serverInstance = server;
    std::signal(SIGINT, signalHandlerWrapper);

    try
    {
        server->startListening();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

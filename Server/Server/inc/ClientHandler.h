#include "RequestProcessor.h"
#include "Helper.h"

class ClientHandler
{
public:
    ClientHandler(int clientSocket);
    void handle();

private:
    int clientSocket;
    bool running;
    RequestProcessor requestProcessor;
    Helper *helper;
    bool sendRequest(std::string request);
    std::string receiveRequest();
};
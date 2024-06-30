#include "RequestProcessor.h"
#include "StringSerializer.h"
class ClientHandler {
public:
    ClientHandler(int clientSocket);
    void handle();

private:
    int clientSocket;
    bool running;
    RequestProcessor requestProcessor;
    StringSerializer stringSerializer;
    
    bool sendRequest(std::vector<std::string> request);
    std::vector<std::string> receiveRequest();
};
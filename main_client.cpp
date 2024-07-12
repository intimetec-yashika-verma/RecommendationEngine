#include "Client.h"
#include "ClientController.h"
#include <iostream>

int main() {
    std::string serverIp = "127.0.0.1"; // Replace with your server's IP address
    int serverPort = 12345; // Replace with your server's port number

    Client *client=new Client(serverIp, serverPort);

    if (!client->connectToServer()) {
        std::cerr << "Failed to connect to server." << std::endl;
        return 1;
    }
    
    ClientController clientController=ClientController(client);
    clientController.run();
    std::vector<std::string> userRole= client->receiveMessage();
    std::cout<<"userRole"<<userRole[0]<<std::endl;
    promptForClient.showMenuPrompt(userRole[0]);
    return 0;
}

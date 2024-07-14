#include "Client.h"
#include "ClientController.h"
#include <iostream>

int main() {
    std::string serverIp = "127.0.0.1"; // Replace with your server's IP address
    int serverPort ; // Replace with your server's port number
    std::cin>>serverPort;
    Client *client=new Client(serverIp, serverPort);

    if (!client->connectToServer()) {
        std::cerr << "Failed to connect to server." << std::endl;
        return 1;
    }
    
    ClientController clientController=ClientController(client);
    clientController.run();
    return 0;
}

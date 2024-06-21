#include "inc/Client.h"
#include "inc/ClientController.h"
#include <iostream>

int main() {
    std::string serverIp = "127.0.0.1"; // Replace with your server's IP address
    int serverPort = 2345; // Replace with your server's port number

    Client *client=new Client(serverIp, serverPort);

    if (!client->connectToServer()) {
        std::cerr << "Failed to connect to server." << std::endl;
        return 1;
    }
    
    ClientController promptForClient=ClientController(client);
    promptForClient.LoginPrompt();
    std::vector<std::string> userRole= client->receiveMessage();
    std::cout<<"userRole"<<userRole[0]<<std::endl;
    promptForClient.showMenuPrompt(userRole[0]);
    // std::string message = email + " " + password;
    
    // if (client.sendMessage(message)) {
    //     std::cout << "Message sent to server: " << message << std::endl;

    //     std::string response = client.receiveMessage();
    //     std::cout << "Server response: " << response << std::endl;
    // } else {
    //     std::cerr << "Failed to send message to server." << std::endl;
    // }

    return 0;
}

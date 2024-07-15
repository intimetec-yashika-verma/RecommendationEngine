#include "ClientController.h"
#include "Client.h"
#include "Operation.h"
#include "Feedback.h"
#include <vector>
#include <iostream>
#include <string>
#include <limits>
#include <unordered_map>
#include "MenuItem.h"
#include "IUserInterface.h"
#include "AdminInterface.h"
#include "ChefInterface.h"
#include "EmployeeInterface.h"
#include "LoginCredential.h"

ClientController::ClientController(Client *client)
{
    this->client = client;
}
Role ClientController::loginPrompt()
{
    LoginCredential loginCredentials;
    std::cout << "enter email id: " << std::endl;
    std::cin >> loginCredentials.emailId;
    std::cout << "enter password: " << std::endl;
    std::cin >> loginCredentials.password;
    std::string userInput = std::to_string(Operation::login) + "$" + loginCredentials.serialize();
    client->sendMessage(userInput);
    std::string clientRole = client->receiveMessage();
    return Role(std::stoi(clientRole));
}
void ClientController::run()
{
    bool flag = true;
    while (flag)
    {
        Role role = loginPrompt();
        if (role == Role::invalid)
        {
            std::cout << "Invalid Credentials" << std::endl;
            continue;
        }
        switch (role)
        {
        case Role::admin:
        {
            userInterface = new AdminInterface(client);
            break;
        }
        case Role::chef:
        {
            userInterface = new ChefInterface(client);
            break;
        }
        case Role::employee:
        {
            userInterface = new EmployeeInterface(client);
            break;
        }
        }
        userInterface->showUserMenuPrompt();
    }
}

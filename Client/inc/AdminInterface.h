#pragma once
#include "IUserInterface.h"
#include "Client.h"

class AdminInterface : public IUserInterface
{
public:
    AdminInterface(Client *client);
    void showUserMenuPrompt();
    void showAddItemPrompt();
    void showUpdateMenuPrompt();
    void showDeleteItemPrompt();
    void showMenu();
    std::string getDataToUpdate(std::string itemName);

private:
    Client *client;
};
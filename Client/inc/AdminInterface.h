#pragma once
#include "IUserInterface.h"
#include "Client.h"
#include "Helper.h"

class AdminInterface : public IUserInterface
{
public:
    AdminInterface(Client *client);
    std::string getDataToUpdate(std::string itemName);
    void showUserMenuPrompt();
    void showAddItemPrompt();
    void showUpdateMenuPrompt();
    void showDeleteItemPrompt();
    void showMenu();
    void logout();

private:
    Helper *helper;
    Client *client;
};
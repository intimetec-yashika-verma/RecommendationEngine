#pragma once
#include "Client.h"
#include "Role.h"
#include "IUserInterface.h"
class ClientController
{
public:
    ClientController(Client *client);
    void run();
    Role loginPrompt();

private:
    Client *client;
    IUserInterface *userInterface;
};
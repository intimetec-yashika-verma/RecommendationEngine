#include "Client.h"

class ClientController
{
public:
    ClientController(Client *client);
    void LoginPrompt();
    void showMenuPrompt(std::string userRole);
    int showAdminMenu();
    void showMenu();
    void showUpdateMenuPrompt();
     void showDeleteItemPrompt();
    void showAddItemPrompt();
   std::vector<std::string> getDataToUpdate();

private:
    Client *client;
};
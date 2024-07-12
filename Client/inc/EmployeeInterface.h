#include "IUserInterface.h"
#include "Client.h"
class EmployeeInterface : public IUserInterface
{
public:
    EmployeeInterface(Client *client);
    void showUserMenuPrompt();

private:
    Client *client;
};
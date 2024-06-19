#include "../inc/LoginService.h"
#include "../inc/Server.h"
#include "../inc/AuthenticationService.h"
#include "../inc/AdminController.h"

LoginService::LoginService()
{
}

std::vector<std::string> LoginService::takeLoginData(int sessionId)
{
    std::vector<std::string> loginCredentials;
    loginCredentials=Server::receiveMessage(sessionId);
    return loginCredentials;
}

bool LoginService::authenticateUser(std::vector<std::string> userCredentials)
{
    AuthenticationService authenticationService = AuthenticationService();
    bool isUserValid = authenticationService.authenticateUser(userCredentials[0], userCredentials[1]);
    return isUserValid;
}
void LoginService::getUserServices(int role)
{
    switch (role)
    {
    case 1:
    {
        std::cout << "admin" << std::endl;
        break;
    }
    case 2:
    {
        std::cout << "chef" << std::endl;
        break;
    }
    case 3:
    {
        std::cout << "employee" << std::endl;
        break;
    }
    }
}

void LoginService::executeRoleBasedFunction(int role,int sessionId)
{
    switch (role)
    {
    case 1:
        AdminController adminController = AdminController(sessionId);
        adminController.loginAdmin();
        break;
    }
}

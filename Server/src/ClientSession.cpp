#include "ClientSession.h"
#include "AuthenticationService.h"
#include "Server.h"


ClientSession::ClientSession(int clientSocket,Server *server)
{
    this->clientSocket=clientSocket;

}

int ClientSession::startSession()
{
    std::vector<std::string> userCredentials = takeUserCredentials();
    AuthenticationService service = AuthenticationService(server->connection);
    bool isUserValid = service.authenticateUser(userCredentials);
    std::string role = fetchRolefromMail(userCredentials[0]);
    int isRoleV = validateRole(role);
    bool isUserValid = loginService.authenticateUser(userCredentials);
    return isUserValid;
}

std::string Session::getRolefromMail(std::string response)
{
    size_t atPos = response.find('@');
    if (atPos == std::string::npos)
    {
        return ""; // Invalid email, no '@' found
    }

    // Find the position of the last '.' after the '@' character
    size_t dotPos = response.find_last_of('.');
    if (dotPos == std::string::npos || dotPos <= atPos)
    {
        return ""; // Invalid email, no '.' found after '@'
    }
    int charCount = dotPos - atPos - 1;
    // Extract and return the domain extension
    return response.substr(atPos + 1, charCount);
}

int Session::validateRole(std::string role)
{
    int enumValue;
    if (role == "admin")
    {
        enumValue = 1;
    }
    else if (role == "chef")
    {
        //std::cout<<"I am Chef";
        enumValue = 2;
    }
    else if (role == "employee")
    {
        enumValue = 3;
    }
    else
    {
        enumValue = 0;
    }
    return enumValue;
}

bool Session::handleUser()
{
    LoginService loginService = LoginService();
    loginService.executeRoleBasedFunction(userRole,sessionId);
}
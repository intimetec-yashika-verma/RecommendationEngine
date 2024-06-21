#include "../inc/Session.h"
#include "../inc/LoginService.h"

bool Session::startSession(int ClientSocket)
{
    this->sessionId = ClientSocket;
    LoginService loginService = LoginService();
    std::vector<std::string> userCredentials = loginService.takeLoginData(ClientSocket);
    std::cout << userCredentials[0] << std::endl;
    std::string role = getRolefromMail(userCredentials[0]);
    std::cout << role << std::endl;
    int enumValue = validateRole(role);
    userRole = enumValue;
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
        std::cout<<"I am Chef";
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
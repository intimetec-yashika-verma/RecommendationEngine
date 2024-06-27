#include <iostream>
#include <vector>
class LoginService
{
public:
    int role;
    enum Roles
    {
        admin = 1,
        chef = 2,
        employee = 3
    };

    LoginService();
    std::vector<std::string> takeLoginData(int sessionId);
    bool authenticateUser(std::vector<std::string> userCredentials);
    void getUserServices(int role);
    void executeRoleBasedFunction(int role,int sessionId);
    static std::vector<std::string> loginData;
};
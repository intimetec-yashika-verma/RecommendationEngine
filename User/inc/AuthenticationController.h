#include <vector>
#include <iostream>
#include "UserService.h"


class AuthenticationController
{
    public:
    UserService* userService;
    AuthenticationController(UserService *userService);
    int authenticateUser(std::vector<std::string> userData);
};
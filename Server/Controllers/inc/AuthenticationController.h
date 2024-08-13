#include <vector>
#include <iostream>
#include "UserService.h"

class AuthenticationController
{
public:
    AuthenticationController(UserService *userService);
    UserProfile authenticateUser(std::string userData);
private:
    UserService *userService;
};
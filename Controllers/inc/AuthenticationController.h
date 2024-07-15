#include <vector>
#include <iostream>
#include "UserService.h"

class AuthenticationController
{
public:
    UserService *userService;
    AuthenticationController(UserService *userService);
    UserProfile authenticateUser(std::string userData);
};
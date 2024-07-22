
#pragma once
#include <string>
#include "DatabaseConnection.h"
// #include "Login.h"
#include "UserDAO.h"
#include "User.h"
#include "UserProfile.h"

class UserService
{
public:
    UserService(UserDAO *userDao);
    UserProfile authenticateUser(std::string userName, std::string password);

private:
    UserDAO *userDAO;
};

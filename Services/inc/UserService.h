
#pragma once
#include <string>
#include "DatabaseConnection.h"
// #include "Login.h"
#include "UserDAO.h"
#include "User.h"

class UserService {
public:
    UserService(UserDAO *userDao);   
    int authenticateUser(std::string userName,std::string password);

private:
   UserDAO *userDAO;
};

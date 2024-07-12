
#pragma once
#include <string>
#include "DatabaseConnection.h"
// #include "Login.h"
#include "UserDAO.h"
#include "User.h"
#include "UserProfile.h"
#include "UserActivityDAO.h"

class UserService {
public:
    UserService(UserDAO *userDao,UserActivityDAO *userActivityDAO);   
    UserProfile authenticateUser(std::string userName,std::string password);
    void saveUserActivity(std::string userName,std::string activity);

private:
   UserDAO *userDAO;
    UserActivityDAO *userActivityDAO;
};

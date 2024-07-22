#include "UserService.h"
// #include "DatabaseConnection.h"
#include "UserDAO.h"
#include "UserActivityDAO.h"
#include <iostream>
#include <vector>

UserService::UserService(UserDAO *userDao) : userDAO(userDao)
{
}
UserProfile UserService::authenticateUser(std::string email, std::string password)
{
    UserProfile userProfile = userDAO->getUserData(email, password);
    if (userProfile.userId == "")
    {
        userProfile.role = "-1";
        return userProfile;
    }
    else
    {
        return userProfile;
    }
}

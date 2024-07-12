#include "UserService.h"
// #include "DatabaseConnection.h"
#include "UserDAO.h"
#include "UserActivityDAO.h"
#include <iostream>
#include <vector>

UserService::UserService(UserDAO *userDao,UserActivityDAO *userActivityDAO) : userDAO(userDao),userActivityDAO(userActivityDAO)
{
}
UserProfile UserService::authenticateUser(std::string email, std::string password)
{
    std::cout<<"authenticateUser"<<std::endl;
    UserProfile userProfile = userDAO->getUserData(email, password);
    saveUserActivity(userProfile.userId, "Login");
    return userProfile;
}

void UserService::saveUserActivity(std::string userId, std::string activity)
{
    userActivityDAO->saveUserActivity(userId, activity);
}
#include "UserService.h"
// #include "DatabaseConnection.h"
#include "UserDAO.h"
#include <iostream>
#include <vector>

UserService::UserService(UserDAO *userDao) : userDAO(userDao)
{
}
int UserService::authenticateUser(std::string email, std::string password)
{
    std::cout<<"authenticateUser"<<std::endl;
    User data = userDAO->getUserData(email, password);
    std::cout<<data.role<<std::endl;
    return data.role;
}

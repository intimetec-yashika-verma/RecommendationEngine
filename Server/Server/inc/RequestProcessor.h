#pragma once
#include <iostream>
#include <vector>
#include "Server.h"
#include "Role.h"
#include "IUserController.h"
#include "UserProfile.h"
#include "Helper.h"
class RequestProcessor
{
private:
    void adminLogin();
    void chefLogin();
    void employeeLogin();

public:
    IUserController *userController;
    RequestProcessor();
    std::string processRequest(std::string request);
    bool isUserLoggedIn = false;
    UserProfile userProfile;
    Helper *helper;
};

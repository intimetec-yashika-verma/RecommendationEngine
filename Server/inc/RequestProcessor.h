#pragma once
#include <iostream>
#include <vector>
#include "Server.h"
#include "Role.h"
#include "IUserController.h"
class RequestProcessor {
    private :
    // AuthenticationController* authenticationController;
    // IUserController* userController;
    // MenuItemService* menuItemService;
    // UserService* userService;
    // FeedbackService* feedbackService;
    // NextDayMenuVotingService* nextDayMenuVotingService;
    // RecommendationService* RecommendationService;

public:
    IUserController* userController;
    RequestProcessor();
    std::vector<std::string> processRequest(std::vector<std::string> request);
    Role userRole;
    bool isUserLoggedIn = false;
    std::string userId;
};


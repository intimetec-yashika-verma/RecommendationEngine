#pragma once
#include <iostream>
#include <vector>
#include "Server.h"
#include "Role.h"
#include "IUserController.h"
#include "UserProfile.h"
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
    std::string processRequest(std::string request);
    bool isUserLoggedIn = false;
    UserProfile userProfile;
};


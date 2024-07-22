#pragma once
#include <vector>
#include <iostream>
#include <unordered_map>
#include "Feedback.h"
#include "FeedbackDAO.h"
#include "UserActivityService.h"
class FeedbackService
{
public:
    FeedbackService(FeedbackDAO *feedbackDAO, UserActivityService *userActivityService);
    std::unordered_map<std::string, std::vector<Feedback>> itemFeedbacks();
    void addItemFeedback(std::string userId, std::unordered_map<std::string, Feedback> itemList);
    void addFeedbackOnDiscaredItem(std::string userId, std::string itemName, std::string negativePoint, std::string improvement, std::string homeReceipe);

private:
    FeedbackDAO *feedbackDAO;
    UserActivityService *userActivityService;
};
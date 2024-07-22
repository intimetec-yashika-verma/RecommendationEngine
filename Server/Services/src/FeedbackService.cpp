#include "FeedbackService.h"
#include "FeedbackDAO.h"
#include "MenuDAO.h"
#include <sstream>
#include <iomanip>

FeedbackService::FeedbackService(FeedbackDAO *feedbackDAO,UserActivityService *userActivityService) : feedbackDAO(feedbackDAO),userActivityService(userActivityService)
{
}

void FeedbackService::addItemFeedback(std::string userId, std::unordered_map<std::string, Feedback> itemList)
{
    for (const auto &item : itemList)
    {
        feedbackDAO->addItemFeedback(userId, item.first, std::to_string(item.second.rating), item.second.comment);
    }
    userActivityService->saveUserActivity(userId,"Added feedback on items");
}

std::unordered_map<std::string, std::vector<Feedback>> FeedbackService::itemFeedbacks()
{
    return feedbackDAO->getItemFeedbacks();
}

void FeedbackService::addFeedbackOnDiscaredItem(std::string userId, std::string itemName, std::string negativePoint, std::string improvement, std::string homeReceipe)
{
    userActivityService->saveUserActivity(userId,"Asked for feedback on Discarded Items"+itemName);
    return feedbackDAO->addFeedbackOnDiscaredItems(userId, itemName, negativePoint, improvement, homeReceipe);
}
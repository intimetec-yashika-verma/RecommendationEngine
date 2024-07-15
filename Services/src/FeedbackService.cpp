#include "FeedbackService.h"
#include "FeedbackDAO.h"
#include "MenuDAO.h"
#include <sstream>
#include <iomanip>

FeedbackService::FeedbackService(FeedbackDAO *feedbackDAO) : feedbackDAO(feedbackDAO)
{
}

void FeedbackService::addItemFeedback(std::string userId, std::unordered_map<std::string, Feedback> itemList)
{
    for (const auto &item : itemList)
    {
        feedbackDAO->addItemFeedback(userId, item.first, std::to_string(item.second.rating), item.second.comment);
    }
}

std::unordered_map<std::string, std::vector<Feedback>> FeedbackService::itemFeedbacks()
{
    return feedbackDAO->getItemFeedbacks();
}

void FeedbackService::addFeedbackOnDiscaredItem(std::string userId, std::string itemName, std::string negativePoint, std::string improvement, std::string homeReceipe)
{
    return feedbackDAO->addFeedbackOnDiscaredItems(userId, itemName, negativePoint, improvement, homeReceipe);
}
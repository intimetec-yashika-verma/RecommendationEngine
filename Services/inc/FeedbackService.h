#include <vector>
#include <iostream>
#include <unordered_map>
#include "Feedback.h"
#include "FeedbackDAO.h"
#pragma once
class FeedbackService
{
public:
    FeedbackService(FeedbackDAO *feedbackDAO);
    std::unordered_map<std::string, std::vector<Feedback>> itemFeedbacks();

    Feedback *getItemFeedback(const std::string &ItemId);

    void addItemFeedback(std::string userId,std::unordered_map<std::string,Feedback> itemList);
    void addFeedbackOnDiscaredItem(std::string userId,std::string itemName,std::string negativePoint,std::string improvement,std::string homeReceipe);

private:
    FeedbackDAO *feedbackDAO;
};
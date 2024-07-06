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
    std::unordered_map<std::string, Feedback> itemFeedbacks;

    Feedback *getItemFeedback(const std::string &ItemId);

    void addItemFeedback(std::vector<std::string> itemList);

private:
    FeedbackDAO *feedbackDAO;
};
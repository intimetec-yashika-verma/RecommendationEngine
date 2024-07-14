#pragma once
#include <iostream>
#include <vector>
#include "FeedbackService.h"
#include <unordered_set>
#include "MenuDAO.h"
#include "FeedbackDAO.h"
#include "ItemReview.h"
#include "UserProfile.h"
#pragma once
class RecommendationService
{
public:
    FeedbackService *feedbackService_{nullptr};
    std::unordered_set<std::string> positiveWords_;
    std::unordered_set<std::string> negativeWords_;
    std::unordered_set<std::string> negationWords_;
    RecommendationService(MenuDAO *menuDao, FeedbackDAO *feedbackDao);
    std::vector<ItemReview> recommendTopFoodItems(std::string mealType,
                                                  const std::unordered_map<std::string, std::vector<Feedback>> &feedbackMap,
                                                  const std::vector<MenuItem> &menuItems);
    std::pair<double, ItemReview> evaluateFoodItem(std::vector<Feedback> feedbacks);
    double analyzeSentiment(const std::string &comment, std::vector<std::string> &foundSentiments);
    std::vector<ItemReview> generateDiscardList(const std::unordered_map<std::string, std::vector<Feedback>> &feedbackMap, const std::vector<MenuItem> &menuItems);
    bool containsNegativeWords(const std::string &comment);
    std::vector<MenuItem> sortRecommendedMenuItemsBasedOnProfile(UserProfile userProfile, std::vector<MenuItem> chefRolloutMenuForNextDay, std::vector<MenuItem> menuItems);
    std::string getMostRepetativeSentiments(const std::vector<std::string>& words);

private:
    MenuDAO *menuDao;
    FeedbackDAO *feedbackDao;
};
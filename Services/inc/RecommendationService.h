#pragma once
#include <iostream>
#include <vector>
#include "FeedbackService.h"
#include <unordered_set>
#include "MenuDAO.h"
#include "FeedbackDAO.h"
#pragma once
class RecommendationService
{
public:
    struct MenuItem
    {
        std::string name;
        std::vector<std::string> foodItems;
        
    };
        FeedbackService *feedbackService_{nullptr};
        std::unordered_set<std::string> positiveWords_;
        std::unordered_set<std::string> negativeWords_;
        std::unordered_set<std::string> negationWords_;
        RecommendationService(MenuDAO *menuDao,FeedbackDAO  *feedbackDao);
        std::vector<std::string> recommendTopFoodItems(std::string mealType);
        double evaluateFoodItem(const std::string &foodItem);
        double analyzeSentiment(const std::string &comment);
        std::vector<std::string> generateDiscardList();
        bool containsNegativeWords(const std::string &comment);
        std::vector<std::string> sortRecommendedMenuItemsBasedOnProfile( const std::string userProfile, 
    const std::vector<std::string> chefRolloutMenuForNextDay);
        private:
        MenuDAO *menuDao ;
        FeedbackDAO  *feedbackDao;
};
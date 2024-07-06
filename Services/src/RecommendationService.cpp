#include "RecommendationService.h"
#include "FeedbackService.h"
#include "Utilities.h"
#include "MenuService.h"
#include <queue>

RecommendationService::RecommendationService() : positiveWords_(Utilities::readWordsFromFile("PositiveWords.txt")),
                                               negativeWords_(Utilities::readWordsFromFile("NegativeWords.txt")),
                                               negationWords_(Utilities::readWordsFromFile("NegationWords.txt"))
{
    // feedbackService_ = new FeedbackService();
}

std::vector<std::string> RecommendationService::recommendTopFoodItems(std::string mealType)
{
    // std::priority_queue<std::pair<double, std::string>> foodItemScores;
    // std::unordered_set<std::string> seenItems;
    // MenuService menuService = MenuService();
    // std::vector<std::string> ids = menuService.getMenuItemIdsForMealType(mealType);
    // //std::cout << "ids" << std::endl;
    // for (const auto &id : ids)
    // {
    //     if (seenItems.find(id) == seenItems.end())
    //     {
    //         double score = evaluateFoodItem(id);
    //         foodItemScores.push({score, id});
    //        // std::cout << "ids" << std::endl;
    //         seenItems.insert(id);
    //     }
    // }
    // //std::cout << "ids" << std::endl;
    // std::vector<std::string> topFoodItemIds;
    // while (topFoodItemIds.size() < 4 && !foodItemScores.empty())
    // {
    //     topFoodItemIds.push_back(foodItemScores.top().second);
    //     foodItemScores.pop();
    // }
    // //std::cout << "ids" << std::endl;
    // std::vector<std::string> topFoodItemName;
    // for (std::string itemId : topFoodItemIds)
    // {
    //     std::string itemName= menuService.getMenuItemNameFromId(itemId);
    //     topFoodItemName.push_back(itemName);
    // }
    // return topFoodItemName;
}

double RecommendationService::evaluateFoodItem(const std::string &ItemId)
{
    double totalScore = 0.0;

    Feedback *feedback = feedbackService_->getItemFeedback(ItemId);
    double averageSentimentScore = 0.0;

    // for (const auto &comment : feedback.comments)
    //     averageSentimentScore += analyzeSentiment(comment);
    averageSentimentScore += analyzeSentiment(feedback->comment);
    // averageSentimentScore /= feedbackcomments.size();

    totalScore = (averageSentimentScore + feedback->rating) / 2.0;

    return totalScore;
}

double RecommendationService::analyzeSentiment(const std::string &comment)
{
    std::string lowerComment = Utilities::toLower(comment);
    std::vector<std::string> words = Utilities::splitWords(lowerComment);

    int sentimentScore = 0;
    for (size_t i = 0; i < words.size(); ++i)
    {
        std::string word = words[i];
        bool isNegated = (i > 0 && negationWords_.find(words[i - 1]) != negationWords_.end());

        if (isNegated && i > 1 && negationWords_.find(words[i - 2]) != negationWords_.end())
        {
            isNegated = false;
        }

        if (positiveWords_.find(word) != positiveWords_.end())
        {
            sentimentScore += isNegated ? -1 : 1;
        }
        else if (negativeWords_.find(word) != negativeWords_.end())
        {
            sentimentScore += isNegated ? 1 : -1;
        }
    }

    if (sentimentScore > 1)
    {
        sentimentScore = 1;
    }
    else if (sentimentScore < -1)
    {
        sentimentScore = -1;
    }

    return ((sentimentScore + 1) / 2) * 5;
}
#include "RecommendationService.h"
#include "FeedbackService.h"
#include "Utilities.h"
#include "MenuService.h"
#include "MenuDAO.h"
#include <queue>
#include <sstream>
#include <string>

RecommendationService::RecommendationService(MenuDAO *menuDao,FeedbackDAO  *feedbackDao) : positiveWords_(Utilities::readWordsFromFile("PositiveWords.txt")),
                                               negativeWords_(Utilities::readWordsFromFile("NegativeWords.txt")),
                                               negationWords_(Utilities::readWordsFromFile("NegationWords.txt")),menuDao(menuDao),feedbackDao(feedbackDao)
{

}

std::vector<std::string> RecommendationService::recommendTopFoodItems(std::string mealType)
{
    std::vector<std::string> menuItems = menuDao->getMenuItemsForMealType(mealType);
        std::unordered_map<std::string, double> itemScores;

        for (const auto& itemId : menuItems) {
            std::vector<std::pair<std::string, std::string>> feedbacks = feedbackDao->getItemFeedback(itemId);
            double totalScore = 0.0;

            for (const auto& feedback : feedbacks) {
                double score =analyzeSentiment(feedback.second);
                totalScore += score;
            }

            itemScores[itemId] = totalScore;
        }

        std::vector<std::pair<std::string, double>> sortedItems(itemScores.begin(), itemScores.end());
        std::sort(sortedItems.begin(), sortedItems.end(), [](const auto& a, const auto& b) {
            return b.second < a.second;
        });

        std::vector<std::string> recommendedItems;
        for (const auto& item : sortedItems) {
            recommendedItems.push_back(menuDao->getNameFromId(item.first));
        }

        return recommendedItems;
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

 double RecommendationService::analyzeSentiment(const std::string& text) {
        std::istringstream stream(text);
        std::string word;
        int score = 0;
        bool negate = false;

        while (stream >> word) {
            std::transform(word.begin(), word.end(), word.begin(), ::tolower);
            word.erase(std::remove_if(word.begin(), word.end(), ::ispunct), word.end());

            if (negationWords_.find(word) != negationWords_.end()) {
                negate = true;
                continue;
            }

            if (positiveWords_.find(word) != positiveWords_.end()) {
                score += negate ? -1 : 1;
            } else if (negativeWords_.find(word) != negativeWords_.end()) {
                score += negate ? 1 : -1;
            }

            negate = false;
        }
        return score;
    }

std::vector<std::string> RecommendationService::generateDiscardList() {
    std::unordered_map<std::string,std::vector<Feedback>> menuItems = feedbackDao->fetchMenuItemsWithFeedback();
    std::vector<std::string> discardList;
    for (const auto &item : menuItems) {
        double sumRatings = 0;
        int countRatings = 0;
        bool hasNegativeComment = false;

        for (const Feedback &feedback :item.second) {
            sumRatings += feedback.rating;
            countRatings++;
            if (containsNegativeWords(feedback.comment)) {
                hasNegativeComment = true;
            }
        }

        double averageRating = countRatings ? sumRatings / countRatings : 0;

        if (averageRating < 2 || hasNegativeComment) {
            discardList.push_back(item.first);
        }
    }

    return discardList;
}

bool RecommendationService::containsNegativeWords(const std::string &comment) {
    std::vector<std::string> negativeWords = getNegativeWords();
    for (const auto &word : negativeWords) {
        if (comment.find(word) != std::string::npos) {
            return true;
        }
    }
    return false;
}
std::vector<std::string> getNegativeWords() {
    return {"tasteless", "extremely bad", "very poor", "awful", "terrible", "not worth", "bad"};
}

std::vector<std::string> RecommendationService::sortRecommendedMenuItemsBasedOnProfile(
    const std::string userProfile, 
    const std::vector<MenuItem> chefRolloutMenuForNextDay) {

    std::vector<MenuItem> sortedMenuItems = chefRolloutMenuForNextDay;

    std::sort(sortedMenuItems.begin(), sortedMenuItems.end(), [&](const MenuItem& a, const MenuItem& b) {
        int scoreA = 0, scoreB = 0;

            // Evaluate vegetarian preference
            if (userProfile.vegetarianPreference == a.dietaryCategory) scoreA++;
            // Evaluate spice level
            if (userProfile.spiceLevelOption == a.SpiceLevel) scoreA++;
            // Evaluate food preference
            if (userProfile.foodPreference == a.cuisineCategory) scoreA++;
            // Evaluate sweet tooth preference
            if (userProfile.sweetToothPreference == a.Sweet) scoreA++;
    
            if (userProfile.vegetarianPreference == b.dietaryCategory) scoreB++;
            // Evaluate spice level
            if (userProfile.spiceLevelOption == b.SpiceLevel) scoreB++;
            // Evaluate food preference
            if (userProfile.foodPreference == b.cuisineCategory) scoreB++;
            // Evaluate sweet tooth preference
            if (userProfile.sweetToothPreference == b.Sweet) scoreB++;
        

        // Higher score items should come first
        return scoreA > scoreB;
    });

    return sortedMenuItems;
}    
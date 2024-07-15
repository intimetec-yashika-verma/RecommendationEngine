#include "RecommendationService.h"
#include "FeedbackService.h"
#include "MenuService.h"
#include <queue>
#include <sstream>
#include <string>
#include <algorithm>

RecommendationService::RecommendationService()
{
    helper = new Helper();
    positiveWords_ = helper->readWordsFromFile("PositiveWords.txt");
    negativeWords_ = helper->readWordsFromFile("NegativeWords.txt");
    negationWords_ = helper->readWordsFromFile("NegationWords.txt");
}

std::vector<ItemReview> RecommendationService::recommendTopFoodItems(
    std::string mealType,
    const std::unordered_map<std::string, std::vector<Feedback>> &feedbackMap,
    const std::vector<MenuItem> &menuItems)
{
    std::cout << mealType << std::endl;
    std::cout << "feedbackMap size : " << feedbackMap.size() << std::endl;
    std::cout << "menuItems size : " << menuItems.size() << std::endl;
    auto comp = [](const std::pair<double, ItemReview> &a, const std::pair<double, ItemReview> &b)
    {
        return a.first < b.first;
    };

    std::priority_queue<std::pair<double, ItemReview>, std::vector<std::pair<double, ItemReview>>, decltype(comp)> foodItemScores(comp);

    for (const auto &pair : feedbackMap)
    {
        std::string menuItemName = pair.first;
        std::cout << pair.first << std::endl;
        // Find the MenuItem object corresponding to menuItemId
        auto it = std::find_if(menuItems.begin(), menuItems.end(),
                               [&](const MenuItem &item)
                               { return item.itemName == menuItemName; });

        // recommend only available food Items : assumption that avaiablity of items for tomorrow will be updated today only by admin.

        if (it != menuItems.end() && it->mealType == mealType && it->availability == "YES")
        {
            std::pair<double, ItemReview> score = evaluateFoodItem(pair.second);
            score.second.itemName = it->itemName;
            std::cout << "score.first : " << score.first << std::endl;
            std::cout << "score.second.itemName : " << score.second.itemName << std::endl;
            foodItemScores.push({score.first, score.second});
        }
    }

    std::vector<ItemReview> topFoodItems;
    while (topFoodItems.size() < 4 && !foodItemScores.empty())
    {
        ItemReview itemReview = foodItemScores.top().second;
        topFoodItems.push_back(itemReview);
        foodItemScores.pop();
    }

    return topFoodItems;
}

std::string RecommendationService::getMostRepetativeSentiments(const std::vector<std::string> &words)
{
    std::unordered_map<std::string, int> wordCount;

    // Count occurrences of each word
    for (const std::string &word : words)
    {
        wordCount[word]++;
    }

    // Create a vector of pairs (word, count) from the map
    std::vector<std::pair<std::string, int>> wordFreq(wordCount.begin(), wordCount.end());

    // Sort the vector based on count (in descending order)
    std::sort(wordFreq.begin(), wordFreq.end(), [](const auto &a, const auto &b)
              { return a.second > b.second; });

    // Extract top 4 words
    std::vector<std::string> topWords;
    int count = 0;
    for (const auto &pair : wordFreq)
    {
        topWords.push_back(pair.first);
        count++;
        if (count >= 4)
            break;
    }

    // Join top 4 words into a comma-separated string
    std::string result;
    for (size_t i = 0; i < topWords.size(); ++i)
    {
        result += topWords[i];
        if (i < topWords.size() - 1)
        {
            result += ", ";
        }
    }

    return result;
}

std::pair<double, ItemReview> RecommendationService::evaluateFoodItem(std::vector<Feedback> feedbacks)
{
    double totalScore = 0.0;
    double averageSentimentScore = 0.0;
    std::vector<std::string> sentiments;

    for (const auto &feedback : feedbacks)
    {
        averageSentimentScore += analyzeSentiment(feedback.comment, sentiments);
    }

    averageSentimentScore /= feedbacks.size();

    double averageRating = 0.0;
    for (const auto &feedback : feedbacks)
    {
        averageRating += feedback.rating;
    }

    averageRating /= feedbacks.size();
    totalScore = (averageSentimentScore + averageRating) / 2.0;
    for (auto i : sentiments)
    {
        std::cout << "sentiments : " << i << std::endl;
    }
    std::pair<double, ItemReview> result(totalScore, ItemReview("", averageRating, sentiments));
    return result;
}

double RecommendationService::analyzeSentiment(const std::string &comment, std::vector<std::string> &foundSentiments)
{
    std::string lowerComment = helper->toLower(comment);
    std::vector<std::string> words = helper->splitWords(lowerComment);

    int sentimentScore = 0;
    for (size_t i = 0; i < words.size(); ++i)
    {
        std::string word = words[i];
        bool isNegated = (i > 0 && negationWords_.find(words[i - 1]) != negationWords_.end());

        if (isNegated && i > 1 && negationWords_.find(words[i - 2]) != negationWords_.end())
        {
            isNegated = false;
        }
        std::string sentiment;
        if (positiveWords_.find(word) != positiveWords_.end())
        {
            sentimentScore += isNegated ? -1 : 1;
            sentiment = isNegated ? words[i - 1] + " " + word : word;
            if (std::find(foundSentiments.begin(), foundSentiments.end(), sentiment) == foundSentiments.end())
            {
                foundSentiments.push_back(sentiment);
            }
        }
        else if (negativeWords_.find(word) != negativeWords_.end())
        {
            sentimentScore += isNegated ? 1 : -1;
            sentiment = isNegated ? words[i - 1] + " " + word : word;
            if (std::find(foundSentiments.begin(), foundSentiments.end(), sentiment) == foundSentiments.end())
            {
                foundSentiments.push_back(sentiment);
            }
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
    for (auto i : foundSentiments)
    {
        std::cout << "foundSentiments : " << i << std::endl;
    }

    return ((sentimentScore + 1) / 2) * 5;
}

std::vector<ItemReview> RecommendationService::generateDiscardList(
    const std::unordered_map<std::string, std::vector<Feedback>> &feedbackMap,
    const std::vector<MenuItem> &menuItems)
{
    std::vector<ItemReview> discardList;

    for (const auto &pair : feedbackMap)
    {
        std::string menuItemName = pair.first;

        // Find the MenuItem object corresponding to menuItemId
        auto it = std::find_if(menuItems.begin(), menuItems.end(),
                               [&](const MenuItem &item)
                               { return item.itemName == menuItemName; });

        if (it != menuItems.end())
        {
            std::pair<double, ItemReview> score = evaluateFoodItem(pair.second);
            score.second.itemName = it->itemName;
            std::cout << score.second.averageRating << std::endl;
            if (score.first < 3 && score.second.averageRating < 2)
            {
                discardList.push_back(score.second);
                std::cout << "pushing list in it discard Menu list" << std::endl;
            }
        }
    }
    return discardList;
}

std::vector<MenuItem> RecommendationService::sortRecommendedMenuItemsBasedOnProfile(
    UserProfile userProfile,
    std::vector<MenuItem> chefRolloutMenuForNextDay,
    std::vector<MenuItem> menuItems)
{

    std::vector<MenuItem> sortedMenuItems = chefRolloutMenuForNextDay;

    std::sort(sortedMenuItems.begin(), sortedMenuItems.end(), [&](const MenuItem &a, const MenuItem &b)
              {
        int scoreA = 0, scoreB = 0;

        // Get the MenuItem for each NextDayMenuRollOut item
        auto itA = std::find_if(menuItems.begin(), menuItems.end(),
                                [&](const MenuItem& item) { return item.itemName == a.itemName; });
        auto itB = std::find_if(menuItems.begin(), menuItems.end(),
                                [&](const MenuItem& item) { return item.itemName == b.itemName; });

        if (itA != menuItems.end()) {
            // Evaluate vegetarian preference
            if (userProfile.dietaryCategory == itA->dietaryCategory) scoreA++;
            // Evaluate spice level
            if (userProfile.spiceLevel == itA->spiceLevel) scoreA++;
            // Evaluate food preference
            if (userProfile.preferanceType == itA->cuisineCategory) scoreA++;
            // Evaluate sweet tooth preference
            if (userProfile.sweetTooth == itA->sweet) scoreA++;
        }

        if (itB != menuItems.end()) {
            // Evaluate vegetarian preference
            if (userProfile.dietaryCategory == itB->dietaryCategory) scoreB++;
            // Evaluate spice level
            if (userProfile.spiceLevel == itB->spiceLevel) scoreB++;
            // Evaluate food preference
            if (userProfile.preferanceType == itB->cuisineCategory) scoreB++;
            // Evaluate sweet tooth preference
            if (userProfile.sweetTooth == itB->sweet) scoreB++;
        }

        // Higher score items should come first
        return scoreA > scoreB; });

    return sortedMenuItems;
}

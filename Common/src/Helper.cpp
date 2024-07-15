#include <algorithm>
#include <sstream>
#include <fstream>
#include "Helper.h"

std::string toString(std::string comment, double rating)
{
    return comment + "," + std::to_string(rating);
}

std::string Helper::serializeFeedbacks(const std::unordered_map<std::string, Feedback> &feedbacks)
{
    std::ostringstream oss;
    for (const auto &feedback : feedbacks)
    {
        oss << feedback.first << "," << feedback.second.rating << "," << feedback.second.comment << "&";
    }
    oss.seekp(-1, std::ios_base::end); // Remove the last '&' character
    return oss.str();
}

std::string Helper::serializeMenuItems(const MenuItem &menuItem)
{
    std::ostringstream oss;

    oss << menuItem.itemId << ","
        << menuItem.itemName << ","
        << menuItem.availability << ","
        << menuItem.price << ","
        << menuItem.mealType << ","
        << menuItem.dietaryCategory << ","
        << menuItem.spiceLevel << ","
        << menuItem.cuisineCategory << ","
        << menuItem.sweet;
    return oss.str();
}

std::pair<Operation, std::string> Helper::deserializeOperation(const std::string &requestData)
{
    Operation first;
    std::string second;
    size_t pos = requestData.find('$');

    if (pos != std::string::npos)
    {
        first = static_cast<Operation>(std::stoi(requestData.substr(0, pos)));
        second = requestData.substr(pos + 1);
    }
    else
    {
        first = static_cast<Operation>(std::stoi(requestData));
    }
    return std::make_pair(first, second);
}

std::string Helper::serializeMenuItems(const std::vector<MenuItem> &menuItems)
{
    std::ostringstream oss;
    for (const auto &menuItem : menuItems)
    {
        oss << menuItem.itemName << ","
            << menuItem.availability << ","
            << menuItem.price << ","
            << menuItem.mealType << ","
            << menuItem.dietaryCategory << ","
            << menuItem.spiceLevel << ","
            << menuItem.cuisineCategory << ","
            << menuItem.sweet << "&";
    }
    std::string serializedData = oss.str();
    if (!serializedData.empty())
    {
        serializedData.pop_back(); // Remove the last '&' character
    }
    return serializedData;
}

std::string Helper::serializeItemReview(const std::vector<ItemReview> &itemReview)
{
    std::ostringstream oss;
    for (const auto &item : itemReview)
    {
        std::string iss;
        for (int i = 0; i < item.sentiments.size(); i++)
        {
            iss = iss + item.sentiments[i] + ",";
            if (i == item.sentiments.size() - 1)
            {
                iss.pop_back();
            }
        }
        oss << item.itemName << ","
            << item.averageRating << ","
            << iss << "&";
    }
    std::string serializedData = oss.str();
    if (!serializedData.empty())
    {
        serializedData.pop_back(); // Remove the last '&' character
    }
    return serializedData;
}

std::vector<ItemReview> Helper::deserializeItemReview(const std::string &serializedData)
{
    std::vector<ItemReview> itemReviews;
    std::istringstream iss(serializedData);
    std::string itemData;

    while (std::getline(iss, itemData, '&'))
    { // Split by '&' delimiter
        ItemReview itemReview;
        std::istringstream itemStream(itemData);
        std::string segment;
        int segmentCount = 0;

        while (std::getline(itemStream, segment, ','))
        { // Split by ',' delimiter
            switch (segmentCount)
            {
            case 0:
                itemReview.itemName = segment;
                break;
            case 1:
                itemReview.averageRating = std::stod(segment);
                break;
            case 2:
                std::istringstream sentimentsStream(segment);
                std::string sentiment;
                while (std::getline(sentimentsStream, sentiment, ','))
                {
                    itemReview.sentiments.push_back(sentiment);
                }
                break;
            }
            segmentCount++;
        }

        itemReviews.push_back(itemReview);
    }

    return itemReviews;
}

std::string Helper::serializeVoteCount(const std::vector<VoteCount> &voteCounts)
{
    std::ostringstream oss;
    for (const auto &voteCount : voteCounts)
    {
        oss << voteCount.itemName << ","
            << voteCount.count << "&";
    }
    std::string serializedData = oss.str();
    if (!serializedData.empty())
    {
        serializedData.pop_back(); // Remove the last '&' character
    }
    return serializedData;
}

std::vector<VoteCount> Helper::deserializeVoteCountList(const std::string &serializedData)
{
    std::vector<VoteCount> voteCounts;
    std::istringstream iss(serializedData);
    std::string itemData;

    while (std::getline(iss, itemData, '&'))
    { // Split by '&' delimiter
        VoteCount voteCount;
        std::istringstream itemStream(itemData);
        std::string segment;
        int segmentCount = 0;

        while (std::getline(itemStream, segment, ','))
        { // Split by ',' delimiter
            switch (segmentCount)
            {
            case 0:
                voteCount.itemName = segment;
                break;
            case 1:
                voteCount.count = std::stoi(segment);
                break;
            }
            segmentCount++;
        }

        voteCounts.push_back(voteCount);
    }

    return voteCounts;
}

std::unordered_map<std::string, Feedback> Helper::deserializeFeedbacks(const std::string &serializedData)
{
    std::unordered_map<std::string, Feedback> feedbacks;
    std::istringstream iss(serializedData);
    std::string itemData;

    while (std::getline(iss, itemData, '&'))
    { // Split by '&' delimiter
        Feedback feedback;
        std::istringstream itemStream(itemData);
        std::string segment;
        int segmentCount = 0;

        while (std::getline(itemStream, segment, ','))
        { // Split by ',' delimiter
            switch (segmentCount)
            {
            case 0:
                feedback.comment = segment;
                break;
            case 1:
                feedback.rating = std::stod(segment);
                break;
            }
            segmentCount++;
        }

        feedbacks[feedback.comment] = feedback;
    }

    return feedbacks;
}

DiscardedItemReview Helper::deserializeDiscardedItemReview(const std::string &serializedData)
{
    DiscardedItemReview discardedItemReview;
    std::istringstream iss(serializedData);
    std::string itemData;
    std::getline(iss, itemData, ',');
    discardedItemReview.itemName = itemData;
    std::getline(iss, itemData, ',');
    discardedItemReview.negativePointOnItem = itemData;
    std::getline(iss, itemData, ',');
    discardedItemReview.improvementPointOnItem = itemData;
    std::getline(iss, itemData, ',');
    discardedItemReview.homeRecepie = itemData;
    return discardedItemReview;
}

MenuItem Helper::deserializeMenuItem(const std::string &menuItemData)
{
    MenuItem menuItem;
    std::istringstream itemStream(menuItemData);
    std::string segment;
    int segmentCount = 0;

    while (std::getline(itemStream, segment, ','))
    { // Split by ',' delimiter
        switch (segmentCount)
        {
        case 0:
            menuItem.itemId = segment;
            break;
        case 1:
            menuItem.itemName = segment;
            break;
        case 2:
            menuItem.availability = segment;
            break;
        case 3:
            menuItem.price = segment;
            break;
        case 4:
            menuItem.mealType = segment;
            break;
        case 5:
            menuItem.dietaryCategory = segment;
            break;
        case 6:
            menuItem.spiceLevel = segment;
            break;
        case 7:
            menuItem.cuisineCategory = segment;
            break;
        case 8:
            menuItem.sweet = segment;
            break;
        }
        segmentCount++;
    }

    return menuItem;
}

std::vector<MenuItem> Helper::deserializeMenuItems(std::string ItemsData)
{
    std::vector<MenuItem> menuItems;
    std::istringstream iss(ItemsData);
    std::string itemData;

    while (std::getline(iss, itemData, '&'))
    { // Split by '&' delimiter
        MenuItem menuItem;
        std::istringstream itemStream(itemData);
        std::string segment;
        int segmentCount = 0;

        while (std::getline(itemStream, segment, ','))
        { // Split by ',' delimiter
            switch (segmentCount)
            {
            case 0:
                menuItem.itemName = segment;
                break;
            case 1:
                menuItem.availability = segment;
                break;
            case 2:
                menuItem.price = segment;
                break;
            case 3:
                menuItem.mealType = segment;
                break;
            case 4:
                menuItem.dietaryCategory = segment;
                break;
            case 5:
                menuItem.spiceLevel = segment;
                break;
            case 6:
                menuItem.cuisineCategory = segment;
                break;
            case 7:
                menuItem.sweet = segment;
                break;
            }
            segmentCount++;
        }

        menuItems.push_back(menuItem);
    }

    return menuItems;
}

std::string Helper::serialize(std::vector<std::string> data)
{
    std::ostringstream serializedString;
    for (size_t i = 0; i < data.size(); ++i)
    {
        serializedString << data[i];
        if (i != data.size() - 1)
        {
            serializedString << ",";
        }
    }
    return serializedString.str();
}

std::vector<std::string> Helper::deserialize(const std::string &data)
{
    std::vector<std::string> splittedString;
    std::istringstream iss(data);
    std::string sepratedString;

    while (std::getline(iss, sepratedString, ','))
    {
        splittedString.push_back(sepratedString);
    }

    return splittedString;
}

std::string Helper::toLower(const std::string &str)
{
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

std::vector<std::string> Helper::splitWords(const std::string &str)
{
    std::vector<std::string> words;
    std::string word;
    for (char c : str)
    {
        if (std::isspace(c))
        {
            if (!word.empty())
            {
                words.push_back(word);
                word.clear();
            }
        }
        else
        {
            word += c;
        }
    }
    if (!word.empty())
    {
        words.push_back(word);
    }
    return words;
}

std::unordered_set<std::string> Helper::readWordsFromFile(const std::string &filename)
{
    std::unordered_set<std::string> words;
    std::ifstream file(filename);
    std::string word;
    while (file >> word)
    {
        words.insert(word);
    }
    return words;
}

std::vector<std::string> Helper::splitFeedback(const std::string &s)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);

    while (std::getline(tokenStream, token, '&'))
    {
        tokens.push_back(token);
    }

    return tokens;
}
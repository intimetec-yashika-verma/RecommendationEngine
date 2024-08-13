#pragma once
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include "Feedback.h"
#include "MenuItem.h"
#include "Operation.h"
#include "ItemReview.h"
#include "VoteCount.h"
#include "DiscardedItemReview.h"
class Helper
{
public:
    std::string toLower(const std::string &str);
    std::vector<std::string> splitWords(const std::string &str);
    std::unordered_set<std::string> readWordsFromFile(const std::string &filename);
    std::vector<std::string> splitFeedback(const std::string &s);
    std::string serialize(std::vector<std::string> data);
    std::vector<std::string> deserialize(const std::string &data);
    std::pair<Operation, std::string> deserializeOperation(const std::string &userCredentials);
    std::vector<MenuItem> deserializeMenuItems(std::string ItemsData);
    std::string serializeMenuItems(const std::vector<MenuItem> &menuItems);
    std::string serializeItemReview(const std::vector<ItemReview> &itemReviews);
    std::vector<ItemReview> deserializeItemReview(const std::string &serializedData);
    std::string serializeVoteCount(const std::vector<VoteCount> &voteCounts);
    std::vector<VoteCount> deserializeVoteCountList(const std::string &serializedData);
    std::unordered_map<std::string, Feedback> deserializeFeedbacks(const std::string &serializedData);
    DiscardedItemReview deserializeDiscardedItemReview(const std::string &serializedData);
    MenuItem deserializeMenuItem(const std::string &serializedData);
    std::string serializeFeedbacks(const std::unordered_map<std::string, Feedback> &feedbacks);
    std::string serializeMenuItems(const MenuItem &menuItem);
};
#include <utility>
#include <iostream>
#include <vector>
#include <unordered_map>
#include "Operation.h"
#include "MenuItem.h"
#include "VoteCount.h"
#include "DiscardedItemReview.h"
#include "ItemReview.h"
#include "Feedback.h"
class RequestSerializer
{
  public:
  static std::pair<Operation, std::string> deserializeOperation(const std::string& userCredentials);
  static MenuItem deserializeMenuItems(std::vector<std::string> ItemsData);
  static std::string serializeMenuItems(const std::vector<MenuItem>& menuItems);
  static std::string serializeItemReview(const std::vector<ItemReview>& itemReviews);
  static std::vector<ItemReview> deserializeItemReview(const std::string& serializedData);
  static std::string serializeVoteCount(const std::vector<VoteCount>& voteCounts);
  static std::vector<VoteCount> deserializeVoteCountList(const std::string& serializedData);
  static std::unordered_map<std::string, Feedback> deserializeFeedbacks(const std::string& serializedData);
  static DiscardedItemReview deserializeDiscardedItemReview(const std::string& serializedData);
  static MenuItem deserializeMenuItem(const std::string& serializedData);
};

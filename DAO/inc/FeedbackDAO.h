#include "Feedback.h"
#include <unordered_map>
class FeedbackDAO
{
    public:
    Feedback* getItemFeedback(const std::string &item);
    std::unordered_map<std::string, Feedback> getFeedbacks();
};


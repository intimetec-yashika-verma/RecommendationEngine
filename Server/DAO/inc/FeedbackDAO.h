#pragma once
#include <vector>
#include <unordered_map>
#include "Feedback.h"
#include "DatabaseConnection.h"
class FeedbackDAO
{
public:
    FeedbackDAO();
    std::string getLastUserId();
    std::unordered_map<std::string, std::vector<Feedback>> getItemFeedbacks();
    std::unordered_map<std::string, Feedback> getFeedbacks();
    void addItemFeedback(std::string userId, std::string itemName, std::string rating, std::string comment);
    std::pair<std::string, std::vector<Feedback>> getItemFeedback(const std::string &itemId);
    void addFeedbackOnDiscaredItems(std::string userId, std::string itemName, std::string negativePoint, std::string improvement, std::string homeReceipe);

private:
    DatabaseConnection *dbConnection;
    MYSQL *connection;
};

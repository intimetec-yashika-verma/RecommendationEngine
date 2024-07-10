#pragma once
#include "Feedback.h"
#include <unordered_map>
#include "DatabaseConnection.h"
class FeedbackDAO
{
public:
    FeedbackDAO();
    std::string getLastUserId();
    std::vector<std::pair<std::string, std::string>> getItemFeedback(const std::string &item);
    std::unordered_map<std::string, Feedback> getFeedbacks();
    void addItemFeedback(std::string id, std::string itemName, std::string rating, std::string comment);
    std::unordered_map<std::string, std::vector<Feedback>> fetchMenuItemsWithFeedback();

private:
    DatabaseConnection *dbConnection;
    MYSQL *connection;
};

#pragma once
#include "Feedback.h"
#include <unordered_map>
#include "DatabaseConnection.h"
class FeedbackDAO
{
public:
FeedbackDAO();
std::string getLastUserId();
    Feedback *getItemFeedback(const std::string &item);
    std::unordered_map<std::string, Feedback> getFeedbacks();
    void addItemFeedback(std::string id,std::string itemName, std::string rating, std::string comment);


private:
    DatabaseConnection *dbConnection;
    MYSQL *connection;
};

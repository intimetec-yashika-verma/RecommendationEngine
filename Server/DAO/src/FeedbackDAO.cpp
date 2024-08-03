#include "Feedback.h"
#include "FeedbackDAO.h"
#include "DatabaseConnection.h"

FeedbackDAO::FeedbackDAO() : dbConnection{DatabaseConnection::getInstance()}
{
    connection = dbConnection->getConnection();
}

std::pair<std::string, std::vector<Feedback>> FeedbackDAO::getItemFeedback(const std::string &itemId)
{
    std::pair<std::string, std::vector<Feedback>> itemFeedbacks;
    std::string query = "SELECT rating, comment FROM feedback WHERE itemId ='" + itemId + "'";
    if (mysql_query(connection, query.c_str()))
    {
        throw std::runtime_error("Error in fetching feedback: " + std::string(mysql_error(connection)));
    }
    MYSQL_RES *result = mysql_store_result(connection);
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result)))
    {
        Feedback feedback;
        feedback.rating = std::stoi(row[0]);
        feedback.comment = row[1];
        itemFeedbacks.second.push_back(feedback);
    }
    mysql_free_result(result);
    return itemFeedbacks;
}

void FeedbackDAO::addItemFeedback(std::string userId, std::string itemName, std::string rating, std::string comment)
{
    std::string query = "INSERT INTO Feedback (userId,itemName,rating,comment) VALUES ('" + userId + "','" + itemName + "','" + rating + "','" + comment + "')";
    if (mysql_query(connection, query.c_str()))
    {
        std::cerr << "Query failed: " << mysql_error(connection) << std::endl;
        throw std::runtime_error("Error in adding feedback: " + std::string(mysql_error(connection)));
    }
    else
    {
        std::cout << "Query executed successfully." << std::endl;
    }
}

std::unordered_map<std::string, std::vector<Feedback>> FeedbackDAO::getItemFeedbacks()
{
    std::unordered_map<std::string, std::vector<Feedback>> feedbackMap;
    std::string query = "SELECT MenuItem.name, Feedback.rating, Feedback.comment "
                        "FROM MenuItem JOIN Feedback ON MenuItem.name = Feedback.itemName";
    if (mysql_query(connection, query.c_str()))
    {
        std::cerr << "Query failed: " << mysql_error(connection) << std::endl;
        throw std::runtime_error("Error in fetching feedback: " + std::string(mysql_error(connection)));
    }

    MYSQL_RES *result = mysql_store_result(connection);
    if (!result)
    {
        std::cerr << "Result retrieval failed: " << mysql_error(connection) << std::endl;
        return feedbackMap;
    }

    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result)))
    {
        std::string itemName = row[0];
        Feedback feedback;
        feedback.rating = std::stoi(row[1]);
        feedback.comment = row[2];
        feedbackMap[itemName].push_back(feedback);
    }

    mysql_free_result(result);
    return feedbackMap;
}

void FeedbackDAO::addFeedbackOnDiscaredItems(std::string userId, std::string itemName, std::string negativePoint, std::string improvement, std::string homeReceipe)
{
    std::string query = "INSERT INTO DiscardedMenuItemsFeedback (userId,itemName,negative_point,improvement,home_recipe) VALUES ('" + userId + "','" + itemName + "','" + negativePoint + "','" + improvement + "','" + homeReceipe + "')";
    if (mysql_query(connection, query.c_str()))
    {
        std::cerr << "Query failed: " << mysql_error(connection) << std::endl;
        throw std::runtime_error("Error in adding feedback on discarded items: " + std::string(mysql_error(connection)));
    }
    else
    {
        std::cout << "Query executed successfully." << std::endl;
    }
}
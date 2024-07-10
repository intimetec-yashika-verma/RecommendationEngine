#include "Feedback.h"
#include "FeedbackDAO.h"
#include "DatabaseConnection.h"

FeedbackDAO::FeedbackDAO() : dbConnection{DatabaseConnection::getInstance()}
{
    connection = dbConnection->getConnection();
}

std::string FeedbackDAO::getLastUserId()
{
    std::string lastUserId = "FB000";
    std::string query="SELECT feedbackId FROM feedback ORDER BY feedbackId DESC LIMIT 1";
    if (mysql_query(connection, query.c_str()))
    {
        std::cerr << "Query failed: " << mysql_error(connection) << std::endl;
    }
    else
    {
        std::cout << "Query executed successfully." << std::endl;
    }
    MYSQL_RES *result = mysql_store_result(connection);
    MYSQL_ROW row = mysql_fetch_row(result);
    std::cout<<row[0];
    return row[0];
}
std::vector<std::pair<std::string, std::string>> FeedbackDAO::getItemFeedback(const std::string &itemId)
{
    // std::cout<<"ids"<<std::endl;
    std::vector<std::pair<std::string, std::string>> itemFeedbacks;
    std::string query = "SELECT rating, comment FROM feedback WHERE itemId ='" + itemId + "'";
    mysql_query(connection, query.c_str());
    MYSQL_RES *result = mysql_store_result(connection);
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result)))
    {
        // std::cout<<"yashika"<<row[0]<<std::endl;
        // std::cout<<"yashika"<<row[1]<<std::endl;
        // std::cout<<"ids"<<std::endl;
        std::pair<std::string, std::string> feedback;
        feedback.first = row[0];
        feedback.second = row[1];
        itemFeedbacks.emplace_back(feedback);
        // std::cout<<"ids"<<std::endl;
    }
    mysql_free_result(result);
    return itemFeedbacks;
}

// std::unordered_map<std::string, Feedback> FeedbackDAO::getFeedbacks()
// {
//     std::unordered_map<std::string,Feedback> feedbacks;
//     DatabaseConnection *dbConnection = DatabaseConnection::getInstance();
//     MYSQL *connection = dbConnection->getConnection();

//     std::string query = "SELECT itemId, comment, rating FROM feedback";
//     if (mysql_query(connection, query.c_str()))
//     {
//         std::cerr << "MySQL query error: " << mysql_error(connection) << std::endl;
//         return feedbacks;
//     }

//     MYSQL_RES *result = mysql_store_result(connection);
//     if (result == nullptr)
//     {
//         std::cerr << "MySQL store result error: " << mysql_error(connection) << std::endl;
//         return feedbacks;
//     }

//     MYSQL_ROW row;
//     while ((row = mysql_fetch_row(result)))
//     {
//         Feedback obj;
//         obj.comments = row[1];

//         feedbacks[row[0]]
//         for(int i=1;i<=4;i++)
//         {
//         std::string data = row[i];
//         menuItems.push_back(data);
//         }
//     }
//     for (std::string num : menuItems) {
//         std::cout << num << " ";
//     }
//     std::cout << std::endl;
//     mysql_free_result(result);
//     return menuItems;
// }

// }

void FeedbackDAO::addItemFeedback(std::string id,std::string itemName, std::string rating, std::string comment)
{
    std::string query = "INSERT INTO feedback (feedbackId, userId,itemId,rating,comment) VALUES ('" + id + "', 'USER003','" + itemName + "','" + rating + "','" + comment + "')";
    if (mysql_query(connection, query.c_str()))
    {
        std::cerr << "Query failed: " << mysql_error(connection) << std::endl;
    }
    else
    {
        std::cout << "Query executed successfully." << std::endl;
    }
}

std::unordered_map<std::string,std::vector<Feedback>> FeedbackDAO::fetchMenuItemsWithFeedback()
{
       std::unordered_map<std::string,std::vector<Feedback>> menuItems;
    std::string query = "SELECT MenuItems.id, MenuItems.name, Feedback.rating, Feedback.comment "
                        "FROM MenuItems JOIN Feedback ON MenuItems.id = Feedback.itemId";

    if (mysql_query(connection, query.c_str())) {
        std::cerr << "Query failed: " << mysql_error(connection) << std::endl;
        mysql_close(connection);
        return {};
    }

    MYSQL_RES *result = mysql_store_result(connection);
    if (!result) {
        std::cerr << "Result retrieval failed: " << mysql_error(connection) << std::endl;
        mysql_close(connection);
        return {};
    }  
 
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result))) {
     std::vector<Feedback> feedbacks; 
        Feedback obj;
        obj.rating=std::stoi(row[2]);
        obj.comment=row[3];
        std::string name = row[1];
        feedbacks.push_back(obj);
            if (menuItems.find(name) == menuItems.end()) {
            menuItems[name] = feedbacks;
        }

        menuItems[name].push_back(obj); 
    }

    mysql_free_result(result);
    return menuItems;
}
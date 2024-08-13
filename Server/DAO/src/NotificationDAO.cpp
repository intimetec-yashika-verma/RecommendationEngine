#include "NotificationDAO.h"
#include "DatabaseConnection.h"

#include <iostream>
#include <string>
NotificationDAO::NotificationDAO() : dbConnection{DatabaseConnection::getInstance()}
{
    connection = dbConnection->getConnection();
}
void NotificationDAO::addNewNotification(std::string notificationMessage)
{
    std::cout<<"Adding notification: "<<notificationMessage<<std::endl;
    std::string query = "CALL AddNotificationAndUpdateSeenStatus('" + notificationMessage + "')";
    if (mysql_query(connection, query.c_str()))
    {
        std::cerr << "Query failed: " << mysql_error(connection) << std::endl;
        throw std::runtime_error("Error in adding notification: " + std::string(mysql_error(connection)));
    }
    else
    {
        std::cout << "Query executed successfully." << std::endl;
    }
}

std::vector<std::string> NotificationDAO::getUserNotifcations(std::string userId)
{
    std::string query = "SELECT n.notification_id, n.message FROM Notification n JOIN NotificationSeenStatus nss ON n.notification_id = nss.notification_id WHERE nss.user_id = '" + userId + "' AND nss.seen = FALSE";
    if (mysql_query(connection, query.c_str()))
    {
        std::cerr << "Query failed: " << mysql_error(connection) << std::endl;
        throw std::runtime_error("Error in fetching notifications: " + std::string(mysql_error(connection)));
    }
    else
    {
        std::cout << "Query executed successfully." << std::endl;
    }
    MYSQL_RES *result = mysql_store_result(connection);
    if (result == nullptr)
    {
        std::cerr << "MySQL store result error: " << mysql_error(connection) << std::endl;
    }
    std::vector<std::string> notifications;
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result)))
    {
        notifications.push_back(row[1]);
    }
    mysql_free_result(result);
    setSeenStatus(userId);
    return notifications;
}
void NotificationDAO::setSeenStatus(std::string userId)
{
    std::string updateQuery = "UPDATE NotificationSeenStatus SET seen = TRUE WHERE user_id = '" + userId + "'";
    if (mysql_query(connection, updateQuery.c_str()))
    {
        std::cerr << "Query failed: " << mysql_error(connection) << std::endl;
        throw std::runtime_error("Error in updating seen status: " + std::string(mysql_error(connection)));
    }
    else
    {
        std::cout << "Seen status updated successfully." << std::endl;
    }
}
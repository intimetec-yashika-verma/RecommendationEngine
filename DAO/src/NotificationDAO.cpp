#include "NotificationDAO.h"
#include "DatabaseConnection.h"
#include "StringSerializer.h"
#include <iostream>
#include <string>
NotificationDAO::NotificationDAO() : dbConnection{DatabaseConnection::getInstance()}
{
    connection = dbConnection->getConnection();
}
std::string NotificationDAO::getLastUserId()
{
    std::string lastUserId = "user000";
    mysql_query(connection, "SELECT id FROM Notification ORDER BY id DESC LIMIT 1");
    MYSQL_RES *result = mysql_store_result(connection);
    MYSQL_ROW row = mysql_fetch_row(result);
    return row[0];
}
void NotificationDAO::addNewNotification(std::string generatedId, std::string notificationType, std::string notificationMessage)
{
    std::string query = "INSERT INTO Notification (id,type,message) VALUES ('" + generatedId + "','" + notificationType + "','" + notificationMessage + "')";
    if (mysql_query(connection, query.c_str())) {
        std::cerr << "Query failed: " << mysql_error(connection) << std::endl;
    } else {
        std::cout << "Query executed successfully." << std::endl;
    }
}

std::vector<std::string> NotificationDAO::getUserNotifcations(std::string userId)
{
     std::string query = "SELECT n.id, n.type, n.message FROM Notification n JOIN NotificationSeenStatus nss ON n.id = nss.notification_id WHERE nss.user_id = '"+userId+"' AND nss.seen = FALSE";
    if (mysql_query(connection, query.c_str())) {
        std::cerr << "Query failed: " << mysql_error(connection) << std::endl;
    } else {
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
         notifications.push_back(row[2]);
    }
    mysql_free_result(result);
    return notifications;
}
#include "../inc/NotificationDAO.h"
#include "../inc/DatabaseConnection.h"
#include "../inc/StringSerializer.h"
#include <iostream>
#include <string>

std::string NotificationDAO::getLastUserId()
{
    std::string lastUserId = "user000";
    DatabaseConnection *dbConnection = DatabaseConnection::getInstance();
    MYSQL *connection = dbConnection->getConnection();
    mysql_query(connection, "SELECT id FROM notification ORDER BY id DESC LIMIT 1");
    MYSQL_RES *result = mysql_store_result(connection);
    MYSQL_ROW row = mysql_fetch_row(result);
    return row[0];
}
void NotificationDAO::addNewNotification(std::string generatedId, std::string notificationMessage, std::string notificationType, std::vector<std::string> selectedMenu)
{

    DatabaseConnection *dbConnection = DatabaseConnection::getInstance();
    MYSQL *connection = dbConnection->getConnection();
    StringSerializer stringSerializer = StringSerializer();
    std::string itemList = stringSerializer.serialize(selectedMenu);
    std::string query = "INSERT INTO notification (id,message, notificationType, itemList) VALUES ('"+generatedId+"','" + notificationMessage + "'," + notificationType + ", '" + itemList + "')";
    mysql_query(connection, query.c_str());    
}


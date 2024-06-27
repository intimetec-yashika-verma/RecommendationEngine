#include "NotificationDAO.h"
#include "DatabaseConnection.h"
#include "StringSerializer.h"
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
void NotificationDAO::addNewNotification(std::string generatedId,std::string notificationType, std::string notificationMessage)
{

    DatabaseConnection *dbConnection = DatabaseConnection::getInstance();
    MYSQL *connection = dbConnection->getConnection();
    std::string query = "INSERT INTO notification (id,type, message) VALUES ('"+generatedId+"','" + notificationType + "', '" + notificationMessage + "')";
    mysql_query(connection, query.c_str());    
}


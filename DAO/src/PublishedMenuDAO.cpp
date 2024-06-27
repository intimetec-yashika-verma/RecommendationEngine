#include "PublishedMenuDAO.h"
#include "DatabaseConnection.h"

void PublishedMenuDAO::addItems(std::vector<std::string> itemList)
{
    DatabaseConnection *dbConnection = DatabaseConnection::getInstance();
    MYSQL *connection = dbConnection->getConnection();
    for (int i = 0; i < itemList.size(); i++)
    {
        std::string query = "INSERT INTO PublishedMenu (id) VALUES ('" + itemList[i] + "')";
        mysql_query(connection, query.c_str());
    }
}


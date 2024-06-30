#include "PublishedMenuDAO.h"
#include "DatabaseConnection.h"

PublishedMenuDAO::PublishedMenuDAO(): dbConnection{DatabaseConnection::getInstance()}
{
    connection=dbConnection->getConnection();
}
void PublishedMenuDAO::addItems(std::string itemList)
{
    std::string query = "INSERT INTO PublishedMenu (id) VALUES ('" + itemList + "')";
    mysql_query(connection, query.c_str());
    
}


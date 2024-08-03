#include "PublishedMenuDAO.h"
#include "DatabaseConnection.h"

PublishedMenuDAO::PublishedMenuDAO() : dbConnection{DatabaseConnection::getInstance()}
{
    connection = dbConnection->getConnection();
}
void PublishedMenuDAO::addItems(std::string itemList)
{
    std::string query = "INSERT INTO PublishedMenu (name) VALUES ('" + itemList + "')";
    if (mysql_query(connection, query.c_str()))
    {
        std::cerr << "Query failed: " << mysql_error(connection) << std::endl;
        throw std::runtime_error("Query failed: " + std::string(mysql_error(connection)));
    }
    else
    {
        std::cout << "Query executed successfully." << std::endl;
    }
}

std::vector<std::string> PublishedMenuDAO::getItems()
{
    std::vector<std::string> itemsList;
    std::string query = "SELECT name FROM PublishedMenu";
    if (mysql_query(connection, query.c_str()))
    {
        std::cerr << "MySQL query error: " << mysql_error(connection) << std::endl;
        throw std::runtime_error("Error in fetching items: " + std::string(mysql_error(connection)));
    }
    MYSQL_RES *result = mysql_store_result(connection);
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result)))
    {
        std::string data = row[0];
        itemsList.push_back(data);
        std::cout<<data<<std::endl;
    }
    mysql_free_result(result);
    return itemsList;
}
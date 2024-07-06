#include "PublishedMenuDAO.h"
#include "DatabaseConnection.h"

PublishedMenuDAO::PublishedMenuDAO() : dbConnection{DatabaseConnection::getInstance()}
{
    connection = dbConnection->getConnection();
}
void PublishedMenuDAO::addItems(std::string itemList)
{
    std::string query = "INSERT INTO PublishedMenu (id) VALUES ('" + itemList + "')";
    mysql_query(connection, query.c_str());
}

std::vector<std::string> PublishedMenuDAO::getItems()
{
    std::vector<std::string> itemsList;
    std::string query = "SELECT MenuItems.name FROM PublishedMenu JOIN MenuItems ON PublishedMenu.id = MenuItems.id";
    mysql_query(connection, query.c_str());
    MYSQL_RES *result = mysql_store_result(connection);
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result)))
    {
        std::string data = row[0];
        itemsList.push_back(data);
    }
    // for (std::string id : itemIds) {
    //     std::cout << id << " ";
    // }
    // std::cout << std::endl;
    mysql_free_result(result);
    return itemsList;
}
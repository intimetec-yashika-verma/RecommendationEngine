#include "DiscardItemDAO.h"
#include "ItemReview.h"
#include "Helper.h"

#include <iostream>

DiscardItemDAO::DiscardItemDAO() : dbConnection{DatabaseConnection::getInstance()}
{
    helper = new Helper();
    connection = dbConnection->getConnection();
}
void DiscardItemDAO::addDiscardedItem(std::string itemName, std::string rating, std::string comment)
{
    std::string query = "INSERT INTO DiscardedMenuItem (name, rating, comments) VALUES ('" + itemName + "','" + rating + "','" + comment + "')";
    if (mysql_query(connection, query.c_str()))
    {
        std::cout << "Error in adding discarded item: " << mysql_error(connection) << std::endl;
        throw std::runtime_error("Error in adding discarded item: " + std::string(mysql_error(connection)));
    }
}

std::vector<ItemReview> DiscardItemDAO::getDiscardedItems()
{
    std::vector<ItemReview> discardedItems;
    std::string query = "SELECT name, rating, comments FROM DiscardedMenuItem";
    if (mysql_query(connection, query.c_str()))
    {
        std::cout << "Error in fetching discarded items: " << mysql_error(connection) << std::endl;
        throw std::runtime_error("Error in fetching discarded items: " + std::string(mysql_error(connection)));
    }
    MYSQL_RES *result = mysql_store_result(connection);
    if (result == nullptr)
    {
        std::cout << "Error in storing result: " << mysql_error(connection) << std::endl;
        return discardedItems;
    }
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result)))
    {
        ItemReview obj;
        obj.itemName = row[0];
        obj.averageRating = std::stoi(row[1]);
        obj.sentiments = helper->deserialize(row[2]);
        discardedItems.push_back(obj);
    }
    mysql_free_result(result);
    return discardedItems;
}
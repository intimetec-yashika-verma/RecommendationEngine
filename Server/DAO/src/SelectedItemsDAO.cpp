#include "SelectedItemsDAO.h"
#include "DatabaseConnection.h"
#include "MenuItem.h"
#include "VoteCount.h"
#include "ItemReview.h"

SelectedItemsDAO::SelectedItemsDAO() : dbConnection{DatabaseConnection::getInstance()}
{
    connection = dbConnection->getConnection();
    helper = new Helper();
}
void SelectedItemsDAO::addSlectedItems(std::string itemName, std::string rating, std::string comment)
{
    std::string query = "INSERT INTO ChefSelectedItem (itemName,averageRating,commentSentiments) VALUES ('" + itemName + "'," + rating + ",'" + comment + "')";
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
std::vector<VoteCount> SelectedItemsDAO::getSelectedItemsAndVotes(std::string mealType)
{
    std::string query = "SELECT csi.itemName, csi.voteCount FROM ChefSelectedItem csi JOIN MenuItem mi ON csi.itemName = mi.name WHERE mi.mealType = '" + mealType + "'";
    if (mysql_query(connection, query.c_str()))
    {
        std::cerr << "Query failed: " << mysql_error(connection) << std::endl;
        throw std::runtime_error("Query failed: " + std::string(mysql_error(connection)));
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
    std::vector<VoteCount> itemList;
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result)))
    {
        VoteCount item;
        item.itemName = row[0];
        item.count = std::stoi(row[1]);
        itemList.push_back(item);
    }
    mysql_free_result(result);
    return itemList;
}

std::vector<MenuItem> SelectedItemsDAO::getSelectedItems()
{
    std::string query = "SELECT mi.name mi.dietaryCategory mi.SpiceLevel mi.cuisineCategory mi.Sweet  FROM ChefSelectedItem si JOIN MenuItem mi ON si.name = mi.name WHERE mi.date = '";
    if (mysql_query(connection, query.c_str()))
    {
        std::cerr << "Query failed: " << mysql_error(connection) << std::endl;
        throw std::runtime_error("Query failed: " + std::string(mysql_error(connection)));
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
    std::vector<MenuItem> itemList;
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result)))
    {
        MenuItem item;
        item.itemName = row[0];
        item.dietaryCategory = row[1];
        item.spiceLevel = row[2];
        item.cuisineCategory = row[3];
        item.sweet = row[4];
        itemList.push_back(item);
    }
    mysql_free_result(result);
    return itemList;
}

void SelectedItemsDAO::saveUserVotes(std::string itemName)
{
    std::string query = "UPDATE ChefSelectedItem SET voteCount = voteCount + 1 WHERE itemName = '" + itemName + "'";
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

std::vector<MenuItem> SelectedItemsDAO::getSelectedItemForMealType(std::string mealType)
{
    time_t t = time(0);
    struct tm *now = localtime(&t);
    char date[11];
    strftime(date, sizeof(date), "%Y-%m-%d", now);
    std::string dateString = date;
    std::string query = "SELECT mi.name,  mi.dietaryCategory,  mi.spiceLevel,  mi.cuisineCategory,  mi.isSweet FROM ChefSelectedItem si JOIN MenuItem mi ON si.itemName = mi.name WHERE mi.mealType = '" + mealType + "' AND si.createdAt = '" + dateString + "'";

    if (mysql_query(connection, query.c_str()))
    {
        std::cerr << "Query failed: " << mysql_error(connection) << std::endl;
        throw std::runtime_error("Query failed: " + std::string(mysql_error(connection)));
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
    std::vector<MenuItem> itemList;
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result)))
    {
        MenuItem item;
        item.itemName = row[0];
        item.dietaryCategory = row[1];
        item.spiceLevel = row[2];
        item.cuisineCategory = row[3];
        item.sweet = row[4];
        itemList.push_back(item);
    }
    mysql_free_result(result);
    return itemList;
}

std::vector<ItemReview> SelectedItemsDAO::getSelectedItemsReview()
{
    std::string query = "SELECT itemName, averageRating,commentSentiments FROM ChefSelectedItem";
    if (mysql_query(connection, query.c_str()))
    {
        std::cerr << "Query failed: " << mysql_error(connection) << std::endl;
        throw std::runtime_error("Query failed: " + std::string(mysql_error(connection)));
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
    std::vector<ItemReview> reviewList;
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result)))
    {
        ItemReview review;
        review.itemName = row[0];
        review.averageRating = std::stod(row[1]);
        review.sentiments = helper->deserialize(row[2]);
        reviewList.push_back(review);
    }
    mysql_free_result(result);
    return reviewList;
}
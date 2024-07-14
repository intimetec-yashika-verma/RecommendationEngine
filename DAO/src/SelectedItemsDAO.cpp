#include "SelectedItemsDAO.h"
#include "DatabaseConnection.h"
#include "MenuItem.h"
#include "VoteCount.h"


SelectedItemsDAO::SelectedItemsDAO(): dbConnection{DatabaseConnection::getInstance()}
{
    connection=dbConnection->getConnection();
}
void SelectedItemsDAO::addSlectedItems(std::string itemName)
{
    std::string query = "INSERT INTO ChefSelectedItem (name) VALUES ('" + itemName + "')";
    if (mysql_query(connection, query.c_str())) {
        std::cerr << "Query failed: " << mysql_error(connection) << std::endl;
    } else {
        std::cout << "Query executed successfully." << std::endl;
    }
}
std::vector<VoteCount> SelectedItemsDAO::getSelectedItemsAndVotes(std::string mealType)
{
    std::string query = "SELECT csi.name, csi.vote_count FROM ChefSelectedItem csi JOIN MenuItem mi ON csi.mealType = mi.mealType WHERE mi.mealType = '"+mealType+ "'";
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
    std::vector<VoteCount> itemList;
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result)))
    {
        VoteCount item;
        item.itemName = row[0];
        item.count = std::stoi(row[1]);
        itemList.push_back(item);     
    }
    std::cout << std::endl;
    mysql_free_result(result);
    return itemList;
}

std::vector<MenuItem> SelectedItemsDAO::getSelectedItems()
{
   std::string query = "SELECT mi.name mi.dietaryCategory mi.SpiceLevel mi.cuisineCategory mi.Sweet FROM selectedItem si JOIN MenuItems mi ON si.name = mi.name";
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
    // for (std::string num : itemList) {
    //     std::cout << num << " ";
    // }
    // std::cout << std::endl;
    mysql_free_result(result);
    return itemList;
}

void SelectedItemsDAO::saveUserVotes(std::string itemName)
{
  std::string query = "UPDATE ChefSelectedItem SET voteCount = voteCount + 1 WHERE mi.name = '" + itemName + "'";
   if (mysql_query(connection, query.c_str())) {
        std::cerr << "Query failed: " << mysql_error(connection) << std::endl;
    } else {
        std::cout << "Query executed successfully." << std::endl;
    }
}

std::vector<MenuItem> SelectedItemsDAO::getSelectedItemForMealType(std::string mealType)
{
     std::string query = "SELECT mi.name,  mi.dietaryCategory,  mi.spiceLevel,  mi.cuisineCategory,  mi.isSweet FROM ChefSelectedItem si JOIN MenuItem mi ON si.name = mi.name WHERE mi.mealType = '"+mealType+"'";

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
    // for (std::string num : itemList) {
    //     std::cout << num << " ";
    // }
    // std::cout << std::endl;
    mysql_free_result(result);
    return itemList;
}
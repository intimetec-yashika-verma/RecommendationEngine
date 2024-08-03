#include "MenuDAO.h"
#include "DatabaseConnection.h"
#include "MenuItem.h"

MenuDAO::MenuDAO() : dbConnection{DatabaseConnection::getInstance()}
{
    connection = dbConnection->getConnection();
}

void MenuDAO::addNewItem(std::string userId, std::string name, std::string availablity, std::string price, std::string mealType, std::string dietaryCategory, std::string spiceLevel, std::string cuisineCategory, std::string sweet)
{

    std::string query = "INSERT INTO MenuItem (name, isAvailable, price, mealType, dietaryCategory, spiceLevel, cuisineCategory, isSweet) VALUES ('" + name + "', '" + availablity + "', '" + price + "', '" + mealType + "', '" + dietaryCategory + "', '" + spiceLevel + "', '" + cuisineCategory + "', '" + sweet + "')";
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

void MenuDAO::updateMenuItem(std::string userId, std::string name, std::string propertyName, std::string updatedValue)
{
    std::string query = "UPDATE MenuItem SET " + propertyName + " = '" + updatedValue + "' WHERE name = '" + name + "'";
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

void MenuDAO::removeMenuItem(std::string userId, std::string name)
{
    std::string query = "DELETE FROM MenuItem WHERE name = '" + name + "'";
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

std::vector<MenuItem> MenuDAO::getMenuItems()
{
    std::vector<MenuItem> menuItems;
    std::string query = "SELECT * FROM MenuItem";
    if (mysql_query(connection, query.c_str()))
    {
        std::cerr << "MySQL query error: " << mysql_error(connection) << std::endl;
        throw std::runtime_error("MySQL query error: " + std::string(mysql_error(connection)));
    }

    MYSQL_RES *result = mysql_store_result(connection);
    if (result == nullptr)
    {
        std::cerr << "MySQL store result error: " << mysql_error(connection) << std::endl;
        return menuItems;
    }

    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result)))
    {
        MenuItem item;
        item.itemName = row[1];
        item.availability = row[2];
        item.price = row[3];
        item.mealType = row[4];
        item.dietaryCategory = row[5];
        item.spiceLevel = row[6];
        item.cuisineCategory = row[7];
        item.sweet = row[8];
        menuItems.push_back(item);
    }
    mysql_free_result(result);
    return menuItems;
}
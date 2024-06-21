#include "../inc/MenuDAO.h"
#include "../inc/DatabaseConnection.h"
std::string MenuDAO::getLastUserId()
{
    std::string lastUserId = "user000";
    DatabaseConnection *dbConnection = DatabaseConnection::getInstance();
    MYSQL *connection = dbConnection->getConnection();
    mysql_query(connection, "SELECT userId FROM MenuItems ORDER BY userId DESC LIMIT 1");
    MYSQL_RES *result = mysql_store_result(connection);
    MYSQL_ROW row = mysql_fetch_row(result);
    return row[0];
}
void MenuDAO::addNewItem(std::string itemId, std::string name, std::string price, std::string availablity, std::string mealType)
{
    DatabaseConnection *dbConnection = DatabaseConnection::getInstance();
    MYSQL *connection = dbConnection->getConnection();
    std::string query = "INSERT INTO MenuItems (id, name,availability,price,mealType) VALUES ('" + itemId + "', '" + name + "','" + availablity + "','" + price + "','" + mealType + "')";
    mysql_query(connection, query.c_str());
}
void MenuDAO::updateMenuItem(std::string name, std::string updatedName, std::string price, std::string availablity, std::string mealType)
{
    DatabaseConnection *dbConnection = DatabaseConnection::getInstance();
    MYSQL *connection = dbConnection->getConnection();
    std::string query = "UPDATE MenuItems SET name = '" + updatedName;
    mysql_query(connection, query.c_str());
}

void MenuDAO::removeMenuItem(std::string name)
{
    DatabaseConnection *dbConnection = DatabaseConnection::getInstance();
    MYSQL *connection = dbConnection->getConnection();
    std::string query = "DELETE FROM MenuItems WHERE name = '" + name + "'";
    mysql_query(connection, query.c_str());
}

std::vector<std::string> MenuDAO::fetchMenuItems()
{
    std::vector<std::string> menuItems={"name","availiblity","price","mealType"};
    DatabaseConnection *dbConnection = DatabaseConnection::getInstance();
    MYSQL *connection = dbConnection->getConnection();
    std::string query = "SELECT * FROM MenuItems";
    if (mysql_query(connection, query.c_str()))
    {
        std::cerr << "MySQL query error: " << mysql_error(connection) << std::endl;
        return menuItems;
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
        for(int i=1;i<=4;i++)
        {
        std::string data = row[i];
        menuItems.push_back(data);
        }
    }
    for (std::string num : menuItems) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    mysql_free_result(result);
    return menuItems;
}

std::vector<std::string> MenuDAO::getItemIdsforMealType(std::string mealType)
{
    std::vector<std::string> itemIds;
    DatabaseConnection *dbConnection = DatabaseConnection::getInstance();
    MYSQL *connection = dbConnection->getConnection();
    std::string query = "SELECT id FROM MenuItems WHERE mealType ='"+mealType+"'";
    mysql_query(connection, query.c_str());
    MYSQL_RES *result = mysql_store_result(connection);
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result)))
    {
        std::string data = row[0];
        itemIds.push_back(data);
    }
    for (std::string id : itemIds) {
        std::cout << id << " ";
    }
    std::cout << std::endl;
    mysql_free_result(result);
   return itemIds;

}

std::string MenuDAO::getNameFromId(std::string itemId)
{
    DatabaseConnection *dbConnection = DatabaseConnection::getInstance();
    MYSQL *connection = dbConnection->getConnection();
    std::string query = "SELECT name FROM MenuItems WHERE id ='"+ itemId+"'";
    if (mysql_query(connection, query.c_str()))
    {
        std::cerr << "MySQL query error: " << mysql_error(connection) << std::endl;
        return "";
    }

    MYSQL_RES *result = mysql_store_result(connection);
    if (result == nullptr)
    {
        std::cerr << "MySQL store result error: " << mysql_error(connection) << std::endl;
        return "menuItems";
    }

    MYSQL_ROW row;
    row = mysql_fetch_row(result);
    mysql_free_result(result);
    return row[0];
}

 std::string MenuDAO::getIdFromName(std::string name)
 {
    DatabaseConnection *dbConnection = DatabaseConnection::getInstance();
    MYSQL *connection = dbConnection->getConnection();
    std::string query = "SELECT id FROM MenuItems WHERE name ='"+ name+"'";
    if (mysql_query(connection, query.c_str()))
    {
        std::cerr << "MySQL query error: " << mysql_error(connection) << std::endl;
        return "";
    }

    MYSQL_RES *result = mysql_store_result(connection);
    if (result == nullptr)
    {
        std::cerr << "MySQL store result error: " << mysql_error(connection) << std::endl;
        return "menuItems";
    }
    
    MYSQL_ROW row;
    row = mysql_fetch_row(result);
    std::cout<<row[0]<<std::endl;
    mysql_free_result(result);
    return row[0];
 }
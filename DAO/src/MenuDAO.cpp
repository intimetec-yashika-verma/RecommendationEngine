#include "MenuDAO.h"
#include "DatabaseConnection.h"
#include "MenuItem.h"

MenuDAO::MenuDAO() : dbConnection{DatabaseConnection::getInstance()}
{
    connection = dbConnection->getConnection();
}

void MenuDAO::addNewItem(std::string userId, std::string name, std::string availablity, std::string price, std::string mealType,std::string dietaryCategory, std::string spiceLevel, std::string cuisineCategory, std::string sweet)
{
    std::string query = "CALL AddMenuItem('" + userId + "','" + name + "','" + price + "','" + availablity + "','" + mealType + "','" + dietaryCategory + "','" + spiceLevel + "','" + cuisineCategory + "','" + sweet + "')";
    if (mysql_query(connection, query.c_str()))
    {
        std::cerr << "Query failed: " << mysql_error(connection) << std::endl;
    }
    else
    {
        std::cout << "Query executed successfully." << std::endl;
    }
}
void MenuDAO::updateMenuItem(std::string userId,std::string name, std::string propertyName, std::string updatedValue)
{
    std::string query = "UPDATE MenuItems SET " + propertyName + " = '" + updatedValue + "' WHERE name = '" + name + "'";
    if (mysql_query(connection, query.c_str()))
    {
        std::cerr << "Query failed: " << mysql_error(connection) << std::endl;
    }
    else
    {
        std::string query1 = "INSERT INTO UserActivity (userId, activity) VALUES ("+ userId +",CONCAT('Updated '"+propertyName+" of "+name+"to "+updatedValue+")";
        mysql_query(connection, query1.c_str());
        
        std::string query3 = "INSERT INTO Notification (message) VALUES (CONCAT('Updated '"+propertyName+" of "+name+"to "+updatedValue+")";
        mysql_query(connection, query3.c_str());
        std::string query2 = "SELECT LAST_INSERT_ID() AS notification_id";
        mysql_query(connection, query2.c_str());
        MYSQL_RES *result = mysql_store_result(connection);
         MYSQL_ROW row;
         std::string notificationId;
        while (row = mysql_fetch_row(result))
        {
            notificationId = row[0];
        }
        std::string query4 = "INSERT INTO NotificationSeenStatus (user_id, notification_id) SELECT id,"+notificationId +"FROM User  WHERE Role = 'Employee'";
        if (mysql_query(connection, query4.c_str()))
       {
        std::cerr << "Query failed: " << mysql_error(connection) << std::endl;
        }
        std::cout << "Query executed successfully." << std::endl;

    }
}

void MenuDAO::removeMenuItem(std::string userId,std::string name)
{
    std::string query ="CALL DeleteMenuItemAndNotify('"+name+"','"+userId+"')";
    mysql_query(connection, query.c_str());
}

std::vector<MenuItem> MenuDAO::fetchMenuItems(std::string userId)
{
    std::vector<MenuItem> menuItems;
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
    
        std::string query1 = "INSERT INTO UserActivity (userId, activity) VALUES ("+ userId +",CONCAT('View Menu Items')";
        mysql_query(connection, query1.c_str());
    return menuItems;
}

std::vector<std::string> MenuDAO::getItemIdsforMealType(std::string mealType)
{
    std::vector<std::string> itemIds;
    DatabaseConnection *dbConnection = DatabaseConnection::getInstance();
    MYSQL *connection = dbConnection->getConnection();
    std::string query = "SELECT id FROM MenuItems WHERE mealType ='" + mealType + "'";
    mysql_query(connection, query.c_str());
    MYSQL_RES *result = mysql_store_result(connection);
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result)))
    {
        std::string data = row[0];
        itemIds.push_back(data);
    }
    // for (std::string id : itemIds) {
    //     std::cout << id << " ";
    // }
    // std::cout << std::endl;
    mysql_free_result(result);
    return itemIds;
}

std::string MenuDAO::getNameFromId(std::string itemId)
{
    std::string query = "SELECT name FROM MenuItems WHERE id ='" + itemId + "'";
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
    std::string query = "SELECT id FROM MenuItems WHERE name ='" + name + "'";
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
    std::cout << row[0] << std::endl;
    mysql_free_result(result);
    return row[0];
}

std::vector<std::string> MenuDAO::getMenuItemsForMealType(std::string mealType)
{
    std::vector<std::string> itemsList ;
    std::string query = "SELECT id FROM MenuItems WHERE mealType = '" + mealType + "'";
    mysql_query(connection, query.c_str());
    MYSQL_RES *result = mysql_store_result(connection);
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result)))
    {
        std::string data = row[0];
        itemsList.push_back(data);
    }
    return itemsList;
}
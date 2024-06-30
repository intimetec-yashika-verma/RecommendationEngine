#include "SelectedItemsDAO.h"
#include "DatabaseConnection.h"

SelectedItemsDAO::SelectedItemsDAO(): dbConnection{DatabaseConnection::getInstance()}
{
    connection=dbConnection->getConnection();
}
void SelectedItemsDAO::addSlectedItems(std::string itemId)
{
    std::string query = "INSERT INTO selectedItem (itemid) VALUES ('" + itemId + "')";
    if (mysql_query(connection, query.c_str())) {
        std::cerr << "Query failed: " << mysql_error(connection) << std::endl;
    } else {
        std::cout << "Query executed successfully." << std::endl;
    }
}
std::vector<std::string> SelectedItemsDAO::getSelectedItems()
{
    DatabaseConnection *dbConnection = DatabaseConnection::getInstance();
    MYSQL *connection = dbConnection->getConnection();
    std::string query = "SELECT mi.name, si.voteCount FROM selectedItem si JOIN MenuItems mi ON si.itemid = mi.id";
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
    std::vector<std::string> itemList;
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result)))
    {
        for (int i = 0; i <= 1; i++)
        {
            std::string data = row[i];
            itemList.push_back(data);
        }
    }
    for (std::string num : itemList) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    mysql_free_result(result);
    return itemList;
}
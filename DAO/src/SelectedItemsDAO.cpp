#include "SelectedItemsDAO.h"
#include "DatabaseConnection.h"

void SelectedItemsDAO::addSlectedItems(std::string itemName,std::string itemId)
{
    //std::cout<<itemName<<" "<<itemId<<std::endl;
    DatabaseConnection *dbConnection = DatabaseConnection::getInstance();
    MYSQL *connection = dbConnection->getConnection();
    std::string query = "INSERT INTO selectedItem (itemid, itemname) VALUES ('" + itemName + "', '" + itemId +  "')";
    mysql_query(connection, query.c_str());

}

std::vector<std::string> getSelectedItems()
{
    DatabaseConnection *dbConnection = DatabaseConnection::getInstance();
    MYSQL *connection = dbConnection->getConnection();
    std::string query = "SELECT * FROM SelectedItem";
    mysql_query(connection, query.c_str());

    MYSQL_RES *result = mysql_store_result(connection);
    if (result == nullptr)
    {
        std::cerr << "MySQL store result error: " << mysql_error(connection) << std::endl;
    }
    std::vector<std::string> itemList;
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result)))
    {
        for (int i = 1; i <= 2; i++)
        {
            std::string data = row[i];
            itemList.push_back(data);
        }
    }
    // for (std::string num : menuItems) {
    //     std::cout << num << " ";
    // }
    // std::cout << std::endl;
    mysql_free_result(result);
    return itemList;
}
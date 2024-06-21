#include "../inc/SelectedItemsDAO.h"
#include "../inc/DatabaseConnection.h"

void SelectedItemsDAO::addSlectedItems(std::string itemName,std::string itemId)
{
    std::cout<<itemName<<" "<<itemId<<std::endl;
   DatabaseConnection *dbConnection = DatabaseConnection::getInstance();
    MYSQL *connection = dbConnection->getConnection();
    std::string query = "INSERT INTO selectedItem (itemid, itemname) VALUES ('" + itemName + "', '" + itemId +  "')";
    mysql_query(connection, query.c_str());

}
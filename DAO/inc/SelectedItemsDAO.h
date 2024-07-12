#pragma once
#include <iostream>
#include <vector>
#include "DatabaseConnection.h"
#include "MenuItem.h"

class SelectedItemsDAO
{
public:
    SelectedItemsDAO();
    void addSlectedItems(std::string itemId);
    std::vector<std::string> getSelectedItemsAndVotes();
    std::vector<MenuItem> getSelectedItems();
    void saveUserVotes(std::string itemName);
    
private:
    DatabaseConnection *dbConnection;
    MYSQL *connection;
};
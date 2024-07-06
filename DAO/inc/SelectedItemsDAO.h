#pragma once
#include <iostream>
#include <vector>
#include "DatabaseConnection.h"

class SelectedItemsDAO
{
public:
    SelectedItemsDAO();
    void addSlectedItems(std::string itemId);
    std::vector<std::string> getSelectedItemsAndVotes();
    std::vector<std::string> getSelectedItems();
    void saveUserVotes(std::string itemName);
    
private:
    DatabaseConnection *dbConnection;
    MYSQL *connection;
};
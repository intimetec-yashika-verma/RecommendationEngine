#pragma once
#include <iostream>
#include <vector>
#include "DatabaseConnection.h"
#include "MenuItem.h"
#include "VoteCount.h"

class SelectedItemsDAO
{
public:
    SelectedItemsDAO();
    void addSlectedItems(std::string itemId);
    std::vector<VoteCount> getSelectedItemsAndVotes(std::string mealType);
    std::vector<MenuItem> getSelectedItems();
    void saveUserVotes(std::string itemName);
    std::vector<MenuItem> getSelectedItemForMealType(std::string mealType);
    
private:
    DatabaseConnection *dbConnection;
    MYSQL *connection;
};
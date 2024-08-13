#pragma once
#include <iostream>
#include <vector>
#include "DatabaseConnection.h"
#include "MenuItem.h"
#include "VoteCount.h"
#include "Helper.h"

class SelectedItemsDAO
{
public:
    SelectedItemsDAO();
    void addSlectedItems(std::string itemName, std::string rating, std::string comment);
    std::vector<VoteCount> getSelectedItemsAndVotes(std::string mealType);
    std::vector<MenuItem> getSelectedItems();
    void saveUserVotes(std::string itemName);
    std::vector<MenuItem> getSelectedItemForMealType(std::string mealType);
    std::vector<ItemReview> getSelectedItemsReview();

private:
    Helper *helper;
    DatabaseConnection *dbConnection;
    MYSQL *connection;
};
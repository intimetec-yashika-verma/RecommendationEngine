#pragma once
#include <iostream>
#include <vector>
#include "DatabaseConnection.h"

class SelectedItemsDAO
{
public:
SelectedItemsDAO();
    void addSlectedItems(std::string itemId);
    std::vector<std::string> getSelectedItems();

private:
    DatabaseConnection *dbConnection;
    MYSQL *connection;
};
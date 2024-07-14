#pragma once
#include <vector>
#include "DatabaseConnection.h"
#include "ItemReview.h"

class DiscardItemDAO
{
  public:
  DiscardItemDAO();
    void addDiscardedItem(std::string itemName, std::string rating, std::string comment);
    std::vector<ItemReview> getDiscardedItems();
   private:
    DatabaseConnection *dbConnection;
    MYSQL *connection;
};
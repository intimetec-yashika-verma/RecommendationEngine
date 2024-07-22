#pragma once
#include <vector>
#include "DatabaseConnection.h"
#include "ItemReview.h"
#include "Helper.h"

class DiscardItemDAO
{
public:
  DiscardItemDAO();
  void addDiscardedItem(std::string itemName, std::string rating, std::string comment);
  std::vector<ItemReview> getDiscardedItems();

private:
  Helper *helper;
  DatabaseConnection *dbConnection;
  MYSQL *connection;
};
#pragma once
#include <iostream>
#include <vector>
#include "DatabaseConnection.h"
#include "MenuItem.h"

class MenuDAO
{
public:
  MenuDAO();
  std::string getLastUserId();
  void addNewItem(std::string itemId, std::string name, std::string price, std::string availablity, std::string mealType);
  void updateMenuItem(std::string name, std::string propertyName, std::string updatedValue);
  void removeMenuItem(std::string name);
  std::vector<MenuItem> fetchMenuItems();
  std::vector<std::string> getItemIdsforMealType(std::string mealType);
  std::string getNameFromId(std::string itemId);
  std::string getIdFromName(std::string name);

private:
  DatabaseConnection *dbConnection;
  MYSQL *connection;
};
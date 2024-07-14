#pragma once
#include <iostream>
#include <vector>
#include "DatabaseConnection.h"
#include "MenuItem.h"

class MenuDAO
{
public:
  MenuDAO();
  void addNewItem(std::string itemId, std::string name, std::string price, std::string availablity, std::string mealType, std::string dietaryCategory, std::string spiceLevel, std::string cuisineCategory, std::string sweet);
  void updateMenuItem(std::string userId,std::string name, std::string propertyName, std::string updatedValue);
  void removeMenuItem(std::string userId,std::string name);
  std::vector<MenuItem> fetchMenuItems();
  std::vector<std::string> getItemIdsforMealType(std::string mealType);
  std::string getNameFromId(std::string itemId);
  std::string getIdFromName(std::string name);
   std::vector<std::string> getMenuItemsForMealType(std::string mealType);

private:
  DatabaseConnection *dbConnection;
  MYSQL *connection;
};
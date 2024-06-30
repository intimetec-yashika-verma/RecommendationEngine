#pragma once
#include <iostream>
#include <vector>
#include "MenuDAO.h"
class MenuService
{
public:
   MenuService(MenuDAO *menuDAO);
   bool addItem(std::string name, std::string price, std::string availablity, std::string mealType);
   bool updateItem(std::string name, std::string updatedName, std::string price, std::string availablity, std::string mealType);
   bool removeItem(std::string name);
   std::vector<MenuItem> getMenuItem();
   std::vector<std::string> getMenuItemIdsForMealType(std::string mealType);
   std::string getMenuItemNameFromId(std::string itemId);
   std::string getMenuItemIdFromName(std::string itemName);
   private:
   MenuDAO *menuDAO;
};

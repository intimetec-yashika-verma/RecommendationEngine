#pragma once
#include <iostream>
#include <vector>
#include "MenuDAO.h"
class MenuService
{
public:
   MenuService(MenuDAO *menuDAO);
   bool addItem(std::string userId,std::string name, std::string price, std::string availablity, std::string mealType, std::string dietaryCategory, std::string spiceLevel, std::string cuisineCategory, std::string sweet);
   bool updateItem(std::string userId,std::string name,std::string price, std::string availablity, std::string mealType,std::string dietaryCategory,std::string spiceLevel,std::string cuisineCategory,std::string sweet);
   bool removeItem(std::string userId,std::string name);
   std::vector<MenuItem> getMenuItem();
   std::vector<std::string> getMenuItemIdsForMealType(std::string mealType);
   std::string getMenuItemNameFromId(std::string itemId);
   std::string getMenuItemIdFromName(std::string itemName);
   private:
   MenuDAO *menuDAO;
};

#pragma once
#include <iostream>
#include <vector>
#include "MenuDAO.h"
#include "NotificationService.h"
#include "UserActivityService.h"
class MenuService
{
public:
   MenuService(MenuDAO *menuDAO,NotificationService *notificationService,UserActivityService *userActivityService);
   bool addItem(std::string userId, std::string name, std::string price, std::string availablity, std::string mealType, std::string dietaryCategory, std::string spiceLevel, std::string cuisineCategory, std::string sweet);
   bool updateItem(std::string userId, std::string name, std::string price, std::string availablity, std::string mealType, std::string dietaryCategory, std::string spiceLevel, std::string cuisineCategory, std::string sweet);
   bool removeItem(std::string userId, std::string name);
   std::vector<MenuItem> getMenuItem(std::string userId);
   std::vector<MenuItem> getMenuItem();
private:
   MenuDAO *menuDAO;
   NotificationService *notificationService;
   UserActivityService *userActivityService;
};

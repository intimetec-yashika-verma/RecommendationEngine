#pragma once
#include <iostream>
#include <vector>
#include "IUserController.h"
#include "Operation.h"
#include "MenuService.h"
#include "MenuItem.h"
#include "UserProfile.h"
#include "UserActivityService.h"
#include "NotificationService.h"
#include "Helper.h"
class AdminController : public IUserController
{
public:
  AdminController(MenuService *menuService, UserActivityService *userActivityService, NotificationService *notificationService, UserProfile userProfile);
  std::string addMenuItem(std::string adminChoice);
  std::string updateMenuItem(std::string adminChoice);
  std::string deleteItemFromMenu(std::string adminChoice);
  std::string viewMenuItems();
  std::string handleRequest(std::pair<Operation, std::string> request);

private:
  void addUserActivity(std::string message);
  void addNotification(std::string message);
  UserActivityService *userActivityService;
  NotificationService *notificationService;
  MenuService *menuService;
  UserProfile userProfile;
  Helper *helper;
};
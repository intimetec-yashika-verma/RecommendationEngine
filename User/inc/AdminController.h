#pragma once
#include <iostream>
#include <vector>
#include "IUserController.h"
#include "Operation.h"
#include "MenuService.h"
#include "MenuItem.h"
#include "UserProfile.h"
class AdminController : public IUserController
{
  public:
   AdminController(MenuService *menuService,UserProfile userProfile);
    std::string addMenuItem(std::string adminChoice);
    std::string updateMenuItem(std::string adminChoice);
    std::string deleteItemFromMenu(std::string adminChoice);
    std::string viewMenuItems();
    std::string handleRequest(std::pair<Operation, std::string> request);
  private:
    MenuService *menuService;
    UserProfile userProfile;
};
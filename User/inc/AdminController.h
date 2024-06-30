#pragma once
#include <iostream>
#include <vector>
#include "IUserController.h"
#include "Operation.h"
#include "MenuService.h"
#include "MenuItem.h"
class AdminController : public IUserController
{
  public:
   AdminController(MenuService *menuService);
    std::vector<std::string> addMenuItem(std::vector<std::string> adminChoice);
    std::vector<std::string> updateMenuItem(std::vector<std::string> adminChoice);
    std::vector<std::string> deleteItemFromMenu(std::vector<std::string> adminChoice);
    std::vector<std::string> viewMenuItems();
    std::vector<std::string> handleRequest(std::pair<Operation, std::vector<std::string>> request);
  private:
    MenuService *menuService;
};
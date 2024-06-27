#pragma once
#include <iostream>
#include <vector>
class AdminController
{
  public:
   AdminController(int sessionId);
    void loginAdmin();
    void performAdminAction();
    void addMenuItem(std::vector<std::string> adminChoice);
    void updateMenuItem(std::vector<std::string> adminChoice);
    void deleteItemFromMenu(std::vector<std::string> adminChoice);
    void viewMenuItems();
    int sessionId;
};
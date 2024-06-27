#include "AdminController.h"
#include "Server.h"
#include "AdminService.h"
#include "MenuService.h"
#include <iostream>
#include <vector>
AdminController::AdminController(int sessionId)
{
    this->sessionId = sessionId;
}
void AdminController::loginAdmin()
{
    std::vector<std::string> user;
    user.push_back("1");
    Server::sendMessage(user, sessionId);

    performAdminAction();
}

void AdminController::performAdminAction()
{
    bool flag = true;
    while (flag)
    {
        std::vector<std::string> adminChoice = Server::receiveMessage(sessionId);
        if (adminChoice[0] == "1")
        {

            addMenuItem(adminChoice);
        }
        else if (adminChoice[0] == "2")
        {
            updateMenuItem(adminChoice);
        }
        else if (adminChoice[0] == "3")
        {
            //std::cout<<"deleteItem"<<std::endl;
            deleteItemFromMenu(adminChoice);
        }
        else if (adminChoice[0]=="4")
        {
               viewMenuItems();
        }
    }
}

void AdminController::addMenuItem(std::vector<std::string> adminChoice)
{

    MenuService menuService = MenuService();
    std::string name = adminChoice[1];
    std::string price = adminChoice[2];
    std::string availablity = adminChoice[3];
    std::string mealType = adminChoice[4];
    menuService.addItem(name, price, availablity, mealType);
}

void AdminController::updateMenuItem(std::vector<std::string> adminChoice)
{
    // MenuService menuService = MenuService();
    // std::string name = adminChoice[1];
    // menuService.removeItem(name);
}

void AdminController::deleteItemFromMenu(std::vector<std::string> adminChoice)
{
    MenuService menuService = MenuService();
    std::string name = adminChoice[1];
    menuService.removeItem(name);
}

void AdminController::viewMenuItems()
{
   // std::cout<<"viewMenu"<<std::endl;
    MenuService menuService = MenuService();
    std::vector<std::string> menu=menuService.getMenuItem();
    for (std::string num : menu) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    Server::sendMessage(menu, sessionId);
}
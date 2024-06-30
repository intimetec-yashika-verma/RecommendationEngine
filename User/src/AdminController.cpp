#include "AdminController.h"
#include "Server.h"
#include "AdminService.h"
#include "MenuService.h"
#include "RequestSerializer.h"
#include <iostream>
#include <vector>
AdminController::AdminController(MenuService *menuService) : menuService(menuService)
{
}

std::vector<std::string> AdminController::handleRequest(std::pair<Operation, std::vector<std::string>> request)
{
    std::vector<std::string> response;
    switch (request.first)
    {
    case AddMenuItem:
        std::cout << "addMenuItem" << std::endl;
        response = addMenuItem(request.second);
        break;

    case UpdateMenuItem:
        std::cout << "UpdateMenuItem" << std::endl;
        response = updateMenuItem(request.second);
        break;

    case DeleteMenuItem:
        std::cout << "DeleteMenuItem" << std::endl;
        response = deleteItemFromMenu(request.second);
        break;

    case ViewMenu:
        std::cout<<"ViewMenuItems" <<std::endl;
        response = viewMenuItems(); 
    }

    return response;
}

std::vector<std::string> AdminController::addMenuItem(std::vector<std::string> adminChoice)
{
    std::vector<std::string> response;
    MenuItem itemData = RequestSerializer::deserializeMenuItems(adminChoice);
    std::cout << "item Data" << itemData.itemName << itemData.price << itemData.availability << itemData.mealType << std::endl;
    menuService->addItem(itemData.itemName, itemData.availability, itemData.price, itemData.mealType);
    std::string success = "item added successfully";
    std::cout << success << std::endl;
    response.push_back(success);
    return response;
}

std::vector<std::string> AdminController::updateMenuItem(std::vector<std::string> adminChoice)
{
    for (int i = 0; i < adminChoice.size(); i++)
    {
        std::cout << adminChoice[i] << " ,";
    }
    std::cout << std::endl;
    std::vector<std::string> response;
    std::string updatedName = adminChoice[2];
    std::cout << updatedName << std::endl;
    MenuItem itemData;
    itemData.itemName = adminChoice[1];
    std::cout << itemData.itemName << std::endl;
    itemData.availability = adminChoice[3];
    std::cout << itemData.availability << std::endl;
    itemData.price = adminChoice[4];
    std::cout << itemData.price << std::endl;
    itemData.mealType = adminChoice[5];
    std::cout << itemData.mealType << std::endl;
    std::cout << itemData.itemName + updatedName + itemData.price + itemData.availability + itemData.mealType << std::endl;
    menuService->updateItem(itemData.itemName, updatedName, itemData.price, itemData.availability, itemData.mealType);
    std::string success = "item updated successfully";
    std::cout << success << std::endl;
    response.push_back(success);
    return response;
}

std::vector<std::string> AdminController::deleteItemFromMenu(std::vector<std::string> adminChoice)
{
    std::vector<std::string> response;
    std::string name = adminChoice[1];
    std::cout<<name<<std::endl;
    menuService->removeItem(name);
    std::string success = "Item removed";
    std::cout<<success;
    response.push_back(success);
    return response;
    
}

std::vector<std::string> AdminController::viewMenuItems()
{
    std::vector<MenuItem> menu = menuService->getMenuItem();
    std::vector<std::string> menuList = RequestSerializer::serializeMenuItemToString(menu);
    return menuList;
}
#include "AdminController.h"
#include "Server.h"
#include "AdminService.h"
#include "MenuService.h"
#include "RequestSerializer.h"
#include <iostream>
#include <vector>
AdminController::AdminController(MenuService *menuService, UserProfile userProfile) : menuService(menuService), userProfile(userProfile)
{
}

std::string AdminController::handleRequest(std::pair<Operation, std::string> request)
{
    std::string response;
    switch (request.first)
    {
    case Operation::addMenuItem:
        std::cout << "addMenuItem" << std::endl;
        response = addMenuItem(request.second);
        break;

    case Operation::updateMenuItem:
        std::cout << "UpdateMenuItem" << std::endl;
        response = updateMenuItem(request.second);
        break;

    case Operation::deleteMenuItem:
        std::cout << "DeleteMenuItem" << std::endl;
        response = deleteItemFromMenu(request.second);
        break;

    case Operation::viewMenu:
        std::cout << "ViewMenuItems" << std::endl;
        response = viewMenuItems();
    }

    return response;
}

std::string AdminController::addMenuItem(std::string adminChoice)
{
    std::cout<<"Data to add "<<adminChoice<<std::endl;
    MenuItem itemData = RequestSerializer::deserializeMenuItem(adminChoice);
    std::cout << "item Data" << itemData.itemName << itemData.price << itemData.availability << itemData.mealType << std::endl;
    menuService->addItem(userProfile.userId, itemData.itemName, itemData.availability, itemData.price, itemData.mealType, itemData.dietaryCategory, itemData.spiceLevel, itemData.cuisineCategory, itemData.sweet);
    std::string success = "item added successfully";
    return success;
}

std::string AdminController::updateMenuItem(std::string adminChoice)
{

    MenuItem itemData = RequestSerializer::deserializeMenuItem(adminChoice);
    std::cout << itemData.itemName + itemData.price + itemData.availability + itemData.mealType << std::endl;
    menuService->updateItem(userProfile.userId, itemData.itemName, itemData.price, itemData.availability, itemData.mealType, itemData.dietaryCategory, itemData.spiceLevel, itemData.cuisineCategory, itemData.sweet);
    std::string success = "item updated successfully";
    std::cout << success << std::endl;
    return success;
}

std::string AdminController::deleteItemFromMenu(std::string adminChoice)
{
    menuService->removeItem(userProfile.userId, adminChoice);
    std::string success = "Item removed";
    std::cout << success;
    return success;
}

std::string AdminController::viewMenuItems()
{
    std::vector<MenuItem> menu = menuService->getMenuItem();
    std::string menuList = RequestSerializer::serializeMenuItems(menu);
    return menuList;
}
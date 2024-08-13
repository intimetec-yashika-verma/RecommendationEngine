#include "AdminController.h"
#include "Server.h"
#include "MenuService.h"
#include <iostream>
#include <vector>
AdminController::AdminController(MenuService *menuService,UserProfile userProfile):menuService(menuService),userProfile(userProfile)
{
    helper = new Helper();
}

std::string AdminController::handleRequest(std::pair<Operation, std::string> request)
{
    std::string response;
    switch (request.first)
    {
    case Operation::addMenuItem:
        response = addMenuItem(request.second);
        break;

    case Operation::updateMenuItem:
        response = updateMenuItem(request.second);
        break;

    case Operation::deleteMenuItem:
        response = deleteItemFromMenu(request.second);
        break;

    case Operation::viewMenu:
        response = viewMenuItems();
    }

    return response;
}

std::string AdminController::addMenuItem(std::string adminChoice)
{
    MenuItem itemData = helper->deserializeMenuItem(adminChoice);
    menuService->addItem(userProfile.userId, itemData.itemName, itemData.availability, itemData.price, itemData.mealType, itemData.dietaryCategory, itemData.spiceLevel, itemData.cuisineCategory, itemData.sweet);
    std::string success = "item added successfully";
    return success;
}

std::string AdminController::updateMenuItem(std::string adminChoice)
{

    MenuItem itemData = helper->deserializeMenuItem(adminChoice);
    menuService->updateItem(userProfile.userId, itemData.itemName, itemData.price, itemData.availability, itemData.mealType, itemData.dietaryCategory, itemData.spiceLevel, itemData.cuisineCategory, itemData.sweet);
    std::string success = "item updated successfully";
    return success;
}

std::string AdminController::deleteItemFromMenu(std::string adminChoice)
{
    menuService->removeItem(userProfile.userId, adminChoice);
    std::string success = "Item removed";
    return success;
}

std::string AdminController::viewMenuItems()
{
    std::vector<MenuItem> menu = menuService->getMenuItem();
    std::string menuList = helper->serializeMenuItems(menu);
    return menuList;
}

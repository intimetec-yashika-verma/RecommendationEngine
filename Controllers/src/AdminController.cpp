#include "AdminController.h"
#include "Server.h"
#include "AdminService.h"
#include "MenuService.h"
#include <iostream>
#include <vector>
AdminController::AdminController(MenuService *menuService, UserActivityService *userActivityService, NotificationService *notificationService, UserProfile userProfile) : menuService(menuService), userActivityService(userActivityService), notificationService(notificationService), userProfile(userProfile)
{
    helper = new Helper();
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
    std::cout << "Data to add " << adminChoice << std::endl;
    MenuItem itemData = helper->deserializeMenuItem(adminChoice);
    std::cout << "item Data" << itemData.itemName << itemData.price << itemData.availability << itemData.mealType << std::endl;
    menuService->addItem(userProfile.userId, itemData.itemName, itemData.availability, itemData.price, itemData.mealType, itemData.dietaryCategory, itemData.spiceLevel, itemData.cuisineCategory, itemData.sweet);
    addUserActivity("Added new item :" + itemData.itemName);
    addNotification("New item Added in the menu :" + itemData.itemName);
    std::string success = "item added successfully";
    return success;
}

std::string AdminController::updateMenuItem(std::string adminChoice)
{

    MenuItem itemData = helper->deserializeMenuItem(adminChoice);
    std::cout << itemData.itemName + itemData.price + itemData.availability + itemData.mealType << std::endl;
    menuService->updateItem(userProfile.userId, itemData.itemName, itemData.price, itemData.availability, itemData.mealType, itemData.dietaryCategory, itemData.spiceLevel, itemData.cuisineCategory, itemData.sweet);
    addUserActivity("Updated the item :" + itemData.itemName);
    addNotification("Updated the item  :" + itemData.itemName);
    std::string success = "item updated successfully";
    return success;
}

std::string AdminController::deleteItemFromMenu(std::string adminChoice)
{
    menuService->removeItem(userProfile.userId, adminChoice);
    addUserActivity("deleted the item :" + adminChoice);
    addNotification("deleted the item  :" + adminChoice);
    std::string success = "Item removed";
    std::cout << success;
    return success;
}

std::string AdminController::viewMenuItems()
{
    std::vector<MenuItem> menu = menuService->getMenuItem();
    std::string menuList = helper->serializeMenuItems(menu);
    addUserActivity("Viewed the menu");
    for (int i = 0; i < menu.size(); i++)
    {
        std::cout << menu[i].itemName << " " << menu[i].availability << " " << menu[i].price << " " << menu[i].mealType << " " << menu[i].dietaryCategory << " " << menu[i].spiceLevel << " " << menu[i].cuisineCategory << " " << menu[i].sweet << std::endl;
    }
    std::cout << menuList << std::endl;
    return menuList;
}

void AdminController::addUserActivity(std::string message)
{
    userActivityService->saveUserActivity(userProfile.userId, message);
}

void AdminController::addNotification(std::string message)
{
    notificationService->sendNewNotification(message);
}
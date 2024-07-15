#include "MenuService.h"
#include "MenuDAO.h"
#include <sstream>
#include <iomanip>

MenuService::MenuService(MenuDAO *menuDAO) : menuDAO(menuDAO)
{
}
bool MenuService::addItem(std::string userId, std::string name, std::string availablity, std::string price, std::string mealType, std::string dietaryCategory, std::string spiceLevel, std::string cuisineCategory, std::string sweet)
{

    menuDAO->addNewItem(userId, name, availablity, price, mealType, dietaryCategory, spiceLevel, cuisineCategory, sweet);
    return true;
}

bool MenuService::updateItem(std::string userId, std::string name, std::string price, std::string availability, std::string mealType, std::string dietaryCategory, std::string spiceLevel, std::string cuisineCategory, std::string sweet)
{
    if (price != "0")
    {
        menuDAO->updateMenuItem(userId, name, "price", price);
    }
    if (availability != "0")
    {
        menuDAO->updateMenuItem(userId, name, "availability", availability);
    }
    if (mealType != "0")
    {
        menuDAO->updateMenuItem(userId, name, "mealType", mealType);
    }
    if (dietaryCategory != "0")
    {
        menuDAO->updateMenuItem(userId, name, "dietaryCategory", dietaryCategory);
    }
    if (spiceLevel != "0")
    {
        menuDAO->updateMenuItem(userId, name, "spiceLevel", spiceLevel);
    }
    if (cuisineCategory != "0")
    {
        menuDAO->updateMenuItem(userId, name, "cuisineCategory", cuisineCategory);
    }
    if (sweet != "0")
    {
        menuDAO->updateMenuItem(userId, name, "sweet", sweet);
    }
    return true;
}

bool MenuService::removeItem(std::string userId, std::string name)
{
    menuDAO->removeMenuItem(userId, name);
    return true;
}

std::vector<MenuItem> MenuService::getMenuItem()
{
    std::vector<MenuItem> menuItems = menuDAO->getMenuItems();
    return menuItems;
}

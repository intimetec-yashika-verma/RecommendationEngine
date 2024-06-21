#include "../inc/MenuService.h"
#include "../inc/MenuDAO.h"
#include <sstream>
#include <iomanip>

bool MenuService::addItem(std::string name,std::string price,std::string availablity,std::string mealType)
{
    MenuDAO dao=MenuDAO();
    std::string lastId=dao.getLastUserId();
    std::cout<<"lastId"<<lastId<<std::endl;
    int num = std::stoi(lastId.substr(4)) + 1;

    std::ostringstream oss;
    oss << "ITEM" << std::setw(3) << std::setfill('0') << num;
    std::string newId =oss.str();
    std::cout<<"newId"<<newId<<std::endl;
    dao.addNewItem(newId,name,price,availablity,mealType);
    return true;
} 

bool MenuService::updateItem(std::string name,std::string updatedName,std::string price,std::string availablity,std::string mealType)
{
    MenuDAO dao = MenuDAO();

}

bool MenuService::removeItem(std::string name)
{
     MenuDAO dao = MenuDAO();
     dao.removeMenuItem(name);
}

std::vector<std::string> MenuService::getMenuItem()
{
    MenuDAO dao=MenuDAO();
    std::vector<std::string> menuItems = dao.fetchMenuItems();
    for (std::string num : menuItems) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    return menuItems;
}
 std::vector<std::string> MenuService::getMenuItemIdsForMealType(std::string mealType)
 {
    MenuDAO dao = MenuDAO();
    std::vector<std::string> menuIds = dao.getItemIdsforMealType(mealType);
    return menuIds;

 }
 std::string MenuService::getMenuItemNameFromId(std::string itemId)
 {
   MenuDAO dao = MenuDAO();
   std::string itemName = dao.getNameFromId(itemId);
   return itemName;
 }

 std::string MenuService::getMenuItemIdFromName(std::string itemName)
 {
    MenuDAO dao = MenuDAO();
    std::string id=dao.getIdFromName(itemName);
    return id;
 }
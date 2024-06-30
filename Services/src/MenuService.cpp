#include "MenuService.h"
#include "MenuDAO.h"
#include <sstream>
#include <iomanip>

MenuService::MenuService(MenuDAO *menuDAO):menuDAO(menuDAO)
{

}
bool MenuService::addItem(std::string name,std::string availablity,std::string price,std::string mealType)
{
    std::string lastId=menuDAO->getLastUserId();
    std::cout<<"lastId"<<lastId<<std::endl;
    int num = std::stoi(lastId.substr(4)) + 1;

    std::ostringstream oss;
    oss << "ITEM" << std::setw(3) << std::setfill('0') << num;
    std::string newId =oss.str();
    std::cout<<"newId"<<newId<<std::endl;
    menuDAO->addNewItem(newId,name,availablity,price,mealType);
    return true;
} 

bool MenuService::updateItem(std::string name,std::string updatedName,std::string price,std::string availability,std::string mealType)
{
   if(updatedName!="")
   {
       menuDAO->updateMenuItem(name,"name",updatedName);
   }
   if(price!="")
   {
       menuDAO->updateMenuItem(name,"price",price);
   }
   if(availability!="")
   {
       menuDAO->updateMenuItem(name,"availability",availability);
   }
   if(mealType!="")
   {
    menuDAO->updateMenuItem(name,"mealType",mealType);
   }
   return true;
}

bool MenuService::removeItem(std::string name)
{
    menuDAO->removeMenuItem(name);
    return true;
}

std::vector<MenuItem> MenuService::getMenuItem()
{
    std::vector<MenuItem> menuItems = menuDAO->fetchMenuItems();
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
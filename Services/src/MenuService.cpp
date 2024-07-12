#include "MenuService.h"
#include "MenuDAO.h"
#include <sstream>
#include <iomanip>

MenuService::MenuService(MenuDAO *menuDAO):menuDAO(menuDAO)
{

}
bool MenuService::addItem(std::string userId,std::string name,std::string availablity,std::string price,std::string mealType,std::string dietaryCategory,std::string spiceLevel,std::string cuisineCategory,std::string sweet)
{
 
    menuDAO->addNewItem(userId,name,availablity,price,mealType,dietaryCategory,spiceLevel,cuisineCategory,sweet);
    return true;
} 

bool MenuService::updateItem(std::string userId,std::string name,std::string price,std::string availability,std::string mealType,std::string dietaryCategory,std::string spiceLevel,std::string cuisineCategory,std::string sweet)
{
   if(price!="")
   {
       menuDAO->updateMenuItem(userId,name,"price",price);
   }
   if(availability!="")
   {
       menuDAO->updateMenuItem(userId,name,"availability",availability);
   }
   if(mealType!="")
   {
    menuDAO->updateMenuItem(userId,name,"mealType",mealType);
   }
   if(dietaryCategory!="")
   {
    menuDAO->updateMenuItem(userId,name,"dietaryCategory",dietaryCategory);
   }
   if(spiceLevel!="")
   {
    menuDAO->updateMenuItem(userId,name,"spiceLevel",spiceLevel);
   }
   if(cuisineCategory!="")
   {
    menuDAO->updateMenuItem(userId,name,"cuisineCategory",cuisineCategory);
   }
   if(sweet!="")
   {
    menuDAO->updateMenuItem(userId,name,"sweet",sweet);
   }
   return true;
}

bool MenuService::removeItem(std::string userId,std::string name)
{
    menuDAO->removeMenuItem(userId,name);
    return true;
}

std::vector<MenuItem> MenuService::getMenuItem(std::string userId)
{
    std::vector<MenuItem> menuItems = menuDAO->fetchMenuItems(userId);
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
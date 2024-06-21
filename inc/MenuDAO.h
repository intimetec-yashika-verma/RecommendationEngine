#include <iostream>
#include <vector>
class MenuDAO
{
 public:
 std::string getLastUserId();
 void addNewItem(std::string itemId,std::string name,std::string price,std::string availablity,std::string mealType);
 void updateMenuItem(std::string name,std::string updatedName,std::string price,std::string availablity,std::string mealType);
 void removeMenuItem(std::string name);
 std::vector<std::string> fetchMenuItems();
 std::vector<std::string> getItemIdsforMealType(std::string mealType);
 std::string getNameFromId(std::string itemId);
 std::string getIdFromName(std::string name);
};
#include "RequestSerializer.h"

std::pair<Operation, std::vector<std::string>> RequestSerializer::deserializeOperation(std::vector<std::string> userRequest)
{
    std::pair<Operation,std::vector<std::string>> userResponse;
    int operationInt = std::stoi(userRequest[0]);
    userResponse.first=static_cast<Operation>(operationInt);
    userResponse.second=userRequest;
    return userResponse;
}

Login RequestSerializer::deserializeLoginCredentials(std::vector<std::string> userCredentials)
{
    Login loginCredentials;
    loginCredentials.userName=userCredentials[1];
    loginCredentials.password=userCredentials[2];
    return loginCredentials;
}

MenuItem RequestSerializer::deserializeMenuItems(std::vector<std::string> itemsData)
{
 MenuItem item;
 item.itemName=itemsData[1];
 item.availability=itemsData[2];
 item.price=itemsData[3];
 item.mealType=itemsData[4];
 return item;
}

std::vector<std::string> RequestSerializer::serializeMenuItemToString(std::vector<MenuItem> menuItems)
{
    std::vector<std::string> stringList;
    for(int i=0;i<menuItems.size();i++)
    {
       stringList.push_back(menuItems[i].itemName);
       stringList.push_back(menuItems[i].availability);
       stringList.push_back(menuItems[i].price);
       stringList.push_back(menuItems[i].mealType); 

    }
    return stringList;
}
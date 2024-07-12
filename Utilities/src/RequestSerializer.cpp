#include "RequestSerializer.h"
#include <iostream>
#include <sstream>

std::pair<Operation, std::string>  RequestSerializer::deserializeOperation(const std::string &requestData)
{
      Operation first;
      std::string second;
    size_t pos = requestData.find('$');

    if (pos != std::string::npos) {
        first = static_cast<Operation>(std::stoi(requestData.substr(0, pos)));
        second = requestData.substr(pos + 1);
    }
    else
    {
        first = static_cast<Operation>(std::stoi(requestData));
    }
    return std::make_pair(first, second);
}

std::vector<MenuItem> deserializeMenuItems(const std::string& serializedData) {
    std::vector<MenuItem> menuItems;
    std::istringstream iss(serializedData);
    std::string itemData;

    while (std::getline(iss, itemData, '&')) {  // Split by '&' delimiter
        MenuItem menuItem;
        std::istringstream itemStream(itemData);
        std::string segment;
        int segmentCount = 0;

        while (std::getline(itemStream, segment, ',')) {  // Split by ',' delimiter
            switch (segmentCount) {
                case 0:
                    menuItem.itemName = segment;
                    break;
                case 1: 
                    menuItem.availability = segment;
                    break;      
                case 2: 
                    menuItem.price = segment;
                    break;
                case 3:

                    menuItem.mealType = segment;
                    break;
                case 4:
                    menuItem.dietaryCategory = segment;
                    break;
                case 5:
                    menuItem.spiceLevel = segment;
                    break;  
                case 6:
                    menuItem.cuisineCategory = segment;
                    break;
                case 7:
                    menuItem.sweet = segment;
                    break;             
            }
            segmentCount++;
        }

        menuItems.push_back(menuItem);
    }

    return menuItems;
}

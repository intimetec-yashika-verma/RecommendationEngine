#pragma once
#include <iostream>
#include <sstream>
struct MenuItem
{
    std::string itemId = "0";
    std::string itemName = "0";
    std::string availability = "0";
    std::string price = "0";
    std::string mealType = "0";
    std::string dietaryCategory = "0";
    std::string spiceLevel = "0";
    std::string cuisineCategory = "0";
    std::string sweet = "0";
   
    std::string serialize() const {
        std::ostringstream oss;
        oss << itemId << ","
            << itemName << ","
            << availability << ","
            << price << ","
            << mealType << ","
            << dietaryCategory << ","
            << spiceLevel << ","
            << cuisineCategory << ","
            << sweet;
        return oss.str();
    }
    void deserialize(const std::string& serializedData) {
        MenuItem menuItem;
        std::istringstream iss(serializedData);
        std::getline(iss, menuItem.itemId, ',');
        std::getline(iss, menuItem.itemName, ',');
        std::getline(iss, menuItem.availability, ',');
        std::getline(iss, menuItem.price, ',');
        std::getline(iss, menuItem.mealType, ',');
        std::getline(iss, menuItem.dietaryCategory, ',');
        std::getline(iss, menuItem.spiceLevel, ',');
        std::getline(iss, menuItem.cuisineCategory, ',');
        std::getline(iss, menuItem.sweet);
    }
};

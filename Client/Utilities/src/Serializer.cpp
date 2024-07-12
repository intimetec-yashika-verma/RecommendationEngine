#include "Serializer.h"
#include "MenuItem.h"
#include <sstream>
#include <iostream>

std::string toString(std::string comment,double rating) {
        return comment + "," + std::to_string(rating);
    }

std::string Serializer::serializeFeedbacks(const std::unordered_map<std::string, Feedback>& feedbacks)
{
    std::ostringstream oss;
    for (auto it = feedbacks.begin(); it != feedbacks.end(); ++it) {
        if (it != feedbacks.begin()) {
            oss << ",";
        }
        oss << it->first << "," << toString(it->second.comment,it->second.rating);
    }
    return oss.str();
}

std::string Serializer::serializeMenuItems(const MenuItem& menuItem) {
    std::ostringstream oss;

        oss << menuItem.itemId << ","
            << menuItem.itemName << ","
            << menuItem.availability << ","
            << menuItem.price << ","
            << menuItem.mealType << ","
            << menuItem.dietaryCategory << ","
            << menuItem.SpiceLevel << ","
            << menuItem.cuisineCategory << ","
            << menuItem.Sweet; 
        return oss.str();        
    }




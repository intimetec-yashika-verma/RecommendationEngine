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
    for (const auto& feedback : feedbacks) {
        oss << feedback.first << "," << feedback.second.rating << "," <<feedback.second.comment<< "&";
    }
    oss.seekp(-1, std::ios_base::end); // Remove the last '&' character
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
            << menuItem.spiceLevel << ","
            << menuItem.cuisineCategory << ","
            << menuItem.sweet; 
        return oss.str();        
    }




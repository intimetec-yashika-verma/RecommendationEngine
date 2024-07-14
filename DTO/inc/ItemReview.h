#pragma once
#include <string>
#include <vector>

struct ItemReview {
    std::string itemName;
    double averageRating;
    std::vector<std::string> sentiments;

    ItemReview(const std::string& itemName, double averageRating, const std::vector<std::string>& sentiments)
        : itemName(itemName), averageRating(averageRating), sentiments(sentiments) {}

    ItemReview() = default; 
};

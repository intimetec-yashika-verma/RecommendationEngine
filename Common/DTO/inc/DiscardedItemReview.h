#pragma once
#include <string>
#include <sstream>
struct DiscardedItemReview
{
    std::string itemName;
    std::string negativePointOnItem;
    std::string improvementPointOnItem;
    std::string homeRecepie;

    std::string serialize() const
    {
        std::ostringstream oss;
        oss << itemName << ","
            << negativePointOnItem << ","
            << improvementPointOnItem << ","
            << homeRecepie;
        return oss.str();
    }
};

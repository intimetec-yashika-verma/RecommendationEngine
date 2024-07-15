#pragma once
#include <string>
#include <vector>
#include "DiscardItemDAO.h"
#include "ItemReview.h"
class DiscardMenuItemService

{
public:
    DiscardMenuItemService(DiscardItemDAO *discardItemDAO);
    void addDiscardedItem(std::string itemName, std::string rating, std::string comment);
    std::vector<ItemReview> getDiscardedItems();

private:
    DiscardItemDAO *discardItemDAO;
};

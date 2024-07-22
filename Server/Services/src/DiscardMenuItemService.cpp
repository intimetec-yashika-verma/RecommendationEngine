#include "DiscardMenuItemService.h"
#include "ItemReview.h"
DiscardMenuItemService::DiscardMenuItemService(DiscardItemDAO *discardItemDAO) : discardItemDAO(discardItemDAO)
{
}

void DiscardMenuItemService::addDiscardedItem(std::string itemName, std::string rating, std::string comment)
{
    discardItemDAO->addDiscardedItem(itemName, rating, comment);
}

std::vector<ItemReview> DiscardMenuItemService::getDiscardedItems()
{
    return discardItemDAO->getDiscardedItems();
}
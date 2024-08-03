#include "DiscardMenuItemService.h"
#include "UserActivityService.h"
#include "NotificationService.h"
#include "ItemReview.h"
DiscardMenuItemService::DiscardMenuItemService(DiscardItemDAO *discardItemDAO,UserActivityService *userActivityService,NotificationService *notificationService) : discardItemDAO(discardItemDAO),userActivityService(userActivityService),notificationService(notificationService)
{
}

void DiscardMenuItemService::addDiscardedItem(std::string userId,std::string itemName, std::string rating, std::string comment)
{
    discardItemDAO->addDiscardedItem(itemName, rating, comment);
    userActivityService->saveUserActivity(userId,"Discarded Item"+itemName);
    notificationService->sendNewNotification(userId,"Discarded Item"+itemName);
}

std::vector<ItemReview> DiscardMenuItemService::getDiscardedItems()
{
    return discardItemDAO->getDiscardedItems();
}
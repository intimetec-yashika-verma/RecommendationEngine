#pragma once
#include <string>
#include <vector>
#include "DiscardItemDAO.h"
#include "ItemReview.h"
#include "UserActivityService.h"
#include "NotificationService.h"
class DiscardMenuItemService

{
public:
    DiscardMenuItemService(DiscardItemDAO *discardItemDAO,UserActivityService *userActivityService,NotificationService *notificationService);
    void addDiscardedItem(std::string userId,std::string itemName, std::string rating, std::string comment);
    std::vector<ItemReview> getDiscardedItems();

private:
    DiscardItemDAO *discardItemDAO;
    UserActivityService *userActivityService;
    NotificationService *notificationService;
};

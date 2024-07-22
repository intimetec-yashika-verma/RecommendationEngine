#include "NotificationService.h"
#include "NotificationDAO.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>

NotificationService::NotificationService(NotificationDAO *notificationDAO,UserActivityService *userActivityService) : notificationDAO(notificationDAO),userActivityService(userActivityService)
{
}
void NotificationService::sendNewNotification(std::string userId,std::string message)
{
    notificationDAO->addNewNotification(message);
    userActivityService->saveUserActivity(userId,message);
}

std::vector<std::string> NotificationService::getAllNotifications(std::string userId)
{
    userActivityService->saveUserActivity(userId,"Viewed Notifications");
    return notificationDAO->getUserNotifcations(userId);
}
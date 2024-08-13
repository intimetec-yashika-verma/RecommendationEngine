#include "NotificationService.h"
#include "NotificationDAO.h"
#include "UserActivityService.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>

NotificationService::NotificationService(NotificationDAO *notificationDAO, UserActivityService *userActivityService)
{
      

}
void NotificationService::sendNewNotification(std::string userId, std::string message)
{
    NotificationDAO *notificationDAO = new NotificationDAO();
    UserActivityDAO *userActivityDAO = new UserActivityDAO();
    UserActivityService* userActivityService = new UserActivityService(userActivityDAO);  
    notificationDAO->addNewNotification(message);
    userActivityService->saveUserActivity(userId, message);
}

std::vector<std::string> NotificationService::getAllNotifications(std::string userId)
{
    NotificationDAO *notificationDAO = new NotificationDAO();
    UserActivityDAO *userActivityDAO = new UserActivityDAO();
    UserActivityService* userActivityService = new UserActivityService(userActivityDAO);  
    userActivityService->saveUserActivity(userId, "Viewed Notifications");
    return notificationDAO->getUserNotifcations(userId);
}
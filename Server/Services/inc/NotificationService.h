#pragma once
#include <iostream>
#include <vector>
#include "NotificationDAO.h"
#include "UserActivityService.h"

class NotificationService
{
public:
    NotificationService(NotificationDAO *notificationDAO,UserActivityService *userActivityService);
    void sendNewNotification(std::string userId,std::string message);
    std::vector<std::string> getAllNotifications(std::string userId);

private:
    NotificationDAO *notificationDAO;
    UserActivityService *userActivityService;
};
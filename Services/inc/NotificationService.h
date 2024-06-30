#pragma once
#include <iostream>
#include <vector>
#include "NotificationDAO.h"

class NotificationService
{
    public:
    NotificationService(NotificationDAO *notificationDAO);
    void sendNewNotification(int type,std::string message); 
    std::vector<std::string> getAllNotifications(std::string userId);
    private:
    NotificationDAO *notificationDAO;
};
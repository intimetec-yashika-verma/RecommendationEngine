#pragma once
#include<iostream>
#include <vector>

class NotificationDAO{
    public:
        void addNewNotification(std::string genratedId,std::string notificationType,std::string notificationMessage);
        std::string getLastUserId();
};
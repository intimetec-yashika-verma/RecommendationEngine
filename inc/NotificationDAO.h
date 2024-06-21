#pragma once
#include<iostream>
#include <vector>

class NotificationDAO{
    public:
        void addNewNotification(std::string genratedId,std::string notificationMessage,std::string notificationType,std::vector<std::string> selectedItems);
        std::string getLastUserId();
};
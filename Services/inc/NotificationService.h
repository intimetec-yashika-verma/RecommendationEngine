#pragma once
#include <iostream>
#include <vector>

enum NotificationType
{
    SelectMenu=0,
    NewItemAdded=1,
    ItemUpdated=2
};

class NotificationService
{
    public:
    void sendNewNotification(int type,std::string message); 
    std::vector<std::string> getAllNotifications(std::string userId);
    
};
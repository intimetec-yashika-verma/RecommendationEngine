#pragma once
#include <iostream>
#include <vector>

class NotificationService
{
    public:
    void sendNewNotification(std::string notificationMessage,std::string notificationType,std::vector<std::string> selectedMenuItems); 
    
};
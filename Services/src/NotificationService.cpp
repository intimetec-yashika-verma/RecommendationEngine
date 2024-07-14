#include "NotificationService.h"
#include "NotificationDAO.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>

NotificationService::NotificationService(NotificationDAO *notificationDAO):notificationDAO(notificationDAO)
{

}
void NotificationService::sendNewNotification(std::string message)
{
     notificationDAO->addNewNotification(message);
}

std::vector<std::string> NotificationService::getAllNotifications(std::string userId)
{
    std::cout<<userId<<std::endl;
    return notificationDAO->getUserNotifcations(userId);

}
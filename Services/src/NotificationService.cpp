#include "NotificationService.h"
#include "NotificationDAO.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>

NotificationService::NotificationService(NotificationDAO *notificationDAO):notificationDAO(notificationDAO)
{

}
void NotificationService::sendNewNotification(int type,std::string message)
{

     std::string lastId = notificationDAO->getLastUserId();
     int num = std::stoi(lastId.substr(6)) + 1;

     std::ostringstream oss;
     oss << "NOTIFY" << std::setw(3) << std::setfill('0') << num;
     std::string newId = oss.str();
     std::cout<<newId<<std::endl;
     notificationDAO->addNewNotification(newId,std::to_string(type),message);
}

std::vector<std::string> NotificationService::getAllNotifications(std::string userId)
{
    std::cout<<userId<<std::endl;
    return notificationDAO->getUserNotifcations("USER003");

}
#include "NotificationService.h"
#include "NotificationDAO.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>

void NotificationService::sendNewNotification(int type,std::string message)
{
     NotificationDAO dao = NotificationDAO();
     std::string lastId = dao.getLastUserId();
     int num = std::stoi(lastId.substr(6)) + 1;

     std::ostringstream oss;
     oss << "NOTIFY" << std::setw(3) << std::setfill('0') << num;
     std::string newId = oss.str();

     dao.addNewNotification(newId,std::to_string(type),message);
}

std::vector<std::string> NotificationService::getAllNotifications(std::string userId)
{
    NotificationDAO notification = NotificationDAO();
    std::vector<std::string> data = {"1","abc","2","def"};
    return data;
}
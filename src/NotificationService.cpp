#include "../inc/NotificationService.h"
#include "../inc/NotificationDAO.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>

void NotificationService::sendNewNotification(std::string notificationMessage,std::string notificationType,std::vector<std::string> selectedMenuItems)
{
     NotificationDAO dao = NotificationDAO();
     std::string lastId=dao.getLastUserId();
    std::cout<<"lastId"<<lastId<<std::endl;
    int num = std::stoi(lastId.substr(6)) + 1;

    std::ostringstream oss;
    oss << "NOTIFY" << std::setw(3) << std::setfill('0') << num;
    std::string newId =oss.str();
    std::cout<<"newId"<<newId<<std::endl;

     dao.addNewNotification(newId,notificationMessage,notificationType,selectedMenuItems);
}
    

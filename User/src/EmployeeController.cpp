#include "EmployeeController.h"
#include "NotificationService.h"
#include "Server.h"
#include <vector>
#include <iostream>

 EmployeeController::EmployeeController(NotificationService *notificationService,std::string userId):notificationService(notificationService),userId(userId)
 {

 }

 std::vector<std::string> EmployeeController::handleRequest(std::pair<Operation, std::vector<std::string>> request)
{
    std::vector<std::string> response;
    switch (request.first)
    {
    case ViewNotification:
    {
        std::cout << "ViewNotification" << std::endl;
        response = showNotifications();
        break;
    }
    case VoteItemFromTomorrowMenu:
    {
        std::cout<<"VoteItemFromTomorrowMenu"<<std::endl;
        response = voteForTomorrowMenu(request.second);
        break;
    }      
    }
    return response;
}

std::vector<std::string> EmployeeController::showNotifications()
{
    std::vector<std::string> notifications= notificationService->getAllNotifications(userId);
    return notifications;
}   

std::vector<std::string> EmployeeController::voteForTomorrowMenu()
{
    std::vector<std::string> menuItems = 
}
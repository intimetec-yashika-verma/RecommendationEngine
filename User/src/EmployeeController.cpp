#include "EmployeeController.h"
#include "LoginService.h"
#include "NotificationService.h"
#include "Server.h"
#include <vector>
#include <iostream>


void EmployeeController::loginEmployee()
{
    std::vector<std::string> user;
    user.push_back("3");
    Server::sendMessage(user, sessionId);

    performEmployeeAction();
}

void EmployeeController::performEmployeeAction()
{
    bool flag = true;
    while (flag)
    {
        std::vector<std::string> employeeChoice = Server::receiveMessage(sessionId);
        if (employeeChoice[0] == "1")
        {
            showNotifications();
        }
        else if (employeeChoice[0] == "2")
        {
            
            // updateMenuItem(adminChoice);
        }
        else if (employeeChoice[0] == "3")
        {
            // std::cout<<"deleteItem"<<std::endl;
            // deleteItemFromMenu(adminChoice);
        }
        else if (employeeChoice[0] == "4")
        {
            //    viewMenuItems();
        }
    }
}

void EmployeeController::showNotifications()
{
    std::string userId=LoginService::loginData[0];
    NotificationService notificationService = NotificationService();
    std::vector<std::string> notifications= notificationService.getAllNotifications(userId);
    Server::sendMessage(notifications, sessionId);
    std::vector<std::string> userResponse = Server::receiveMessage(sessionId);
    //send user response to process by notification service
    
}   
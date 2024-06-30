#pragma once
#include "IUserController.h"
#include "NotificationService.h"

class EmployeeController : public IUserController
{
   public:
   EmployeeController(NotificationService* notificationService,std::string userId);
   void loginEmployee();
   void performEmployeeAction();
   std::vector<std::string> showNotifications();
   std::vector<std::string> handleRequest(std::pair<Operation, std::vector<std::string>> userRequest) ;
   std::vector<std::string> voteForTomorrowMenu();
   private:
   NotificationService *notificationService;
   std::string userId;
};
#pragma once
#include "IUserController.h"
#include "NotificationService.h"
#include "SelectionService.h"
#include "FeedbackService.h"
class EmployeeController : public IUserController
{
   public:
   EmployeeController(NotificationService* notificationService,SelectionService *selectionService,FeedbackService *feedbackService,std::string userId);
   void loginEmployee();
   void performEmployeeAction();
   std::vector<std::string> showNotifications();
   std::vector<std::string> handleRequest(std::pair<Operation, std::vector<std::string>> userRequest) ;
   std::vector<std::string> voteForTomorrowMenu();
   std::vector<std::string> getVottedItems(std::vector<std::string> response);
   std::vector<std::string> getItemsListForFeedback();
   std::vector<std::string> getUserFeedback(std::vector<std::string> response);
   private:
   NotificationService *notificationService;
   SelectionService *selectionService;
   FeedbackService *feedbackService;
   std::string userId;
};
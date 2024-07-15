#pragma once
#include "IUserController.h"
#include "NotificationService.h"
#include "SelectionService.h"
#include "FeedbackService.h"
#include "MenuService.h"
#include "PublishMenuService.h"
#include "DiscardMenuItemService.h"
#include "RecommendationService.h"
#include "UserActivityService.h"

class EmployeeController : public IUserController
{
public:
   EmployeeController(NotificationService *notificationService, SelectionService *selectionService, FeedbackService *feedbackService, RecommendationService *recommendationService, MenuService *menuService, PublishMenuService *publishMenuService, DiscardMenuItemService *discardMenuItemService, UserActivityService *userActivityService, UserProfile userProfile);
   std::string showNotifications();
   std::string handleRequest(std::pair<Operation, std::string> userRequest);
   std::string voteForTomorrowMenu(std::string mealType);
   std::string getVotedItems(std::string response);
   std::string getItemsListForFeedback();
   std::string getUserFeedback(std::string response);
   std::string getDiscardedMenuItems();
   std::string getFeedbackOnDiscardedItem(std::string itemName);

private:
   NotificationService *notificationService;
   SelectionService *selectionService;
   FeedbackService *feedbackService;
   RecommendationService *recommendationService;
   PublishMenuService *publishMenuService;
   DiscardMenuItemService *discardMenuItemService;
   UserActivityService *userActivityService;
   UserProfile userProfile;
   MenuService *menuService;
   Helper *helper;
   void addUserActivity(std::string message);
   void addNotification(std::string message);
};
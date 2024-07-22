#pragma once
#include "RecommendationEngine.h"
#include "SelectionService.h"
#include "NotificationService.h"
#include "IUserController.h"
#include "Operation.h"
#include "MenuService.h"
#include "UserProfile.h"
#include "FeedbackService.h"
#include "UserActivityService.h"
#include "PublishMenuService.h"
#include "DiscardMenuItemService.h"
#include "Helper.h"

class ChefController : public IUserController
{
public:
  ChefController(RecommendationEngine *recommendationEngine, SelectionService *selectionService, MenuService *menuService, FeedbackService *feedbackService, PublishMenuService *publishMenuService, DiscardMenuItemService *discardMenuItemService, UserProfile userProfile);
  std::vector<ItemReview> getRecommendedMenu(std::string mealType);
  std::string handleRequest(std::pair<Operation, std::string> request);
  std::string showRecommendations(std::string mealType);
  std::string getSelectedMenu(std::string selectedItems);
  std::string getVotedItemsList(std::string mealType);
  std::string publishTodaysMenu(std::string finalizedMenu);
  std::string getDiscardedMenuItemsList();
  std::string getFeedbackOrHomeReceipe(std::string itemName);

private:
  std::vector<ItemReview> recommendedMenu;
  RecommendationEngine *recommendationEngine;
  SelectionService *selectionService;
  NotificationService *notificationService;
  MenuService *menuService;
  UserProfile userProfile;
  FeedbackService *feedbackService;
  UserActivityService *userActivityService;
  PublishMenuService *publishMenuService;
  DiscardMenuItemService *discardMenuItemService;
  Helper *helper;
};
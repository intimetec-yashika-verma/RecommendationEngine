#pragma once
#include "RecommendationService.h"
#include "SelectionService.h"
#include "NotificationService.h"
#include "IUserController.h"
#include "Operation.h"
#include "MenuService.h"

class ChefController : public IUserController
{
  public:
    ChefController(RecommendationService *recommendationService,SelectionService *selectionService,NotificationService *notificationService,MenuService *menuService);
    void rollOutNextDayMenu(std::vector<std::string>);
    std::vector<std::string> getRecommededMenu(std::string mealType);
    std::vector<std::string> handleRequest(std::pair<Operation, std::vector<std::string>> request);
    std::vector<std::string> showRecommendations(std::vector<std::string> mealType);
    std::vector<std::string> getSelectedMenu(std::vector<std::string> selectedItems);
    std::vector<std::string> getVotedItemsList();
    std::vector<std::string> publishTodaysMenu(std::vector<std::string> finalizedMenu);
    std::vector<std::string> selectedMenu;
    std::vector<std::string> getDiscardedMenuItemsList();
    std::vector<std::string> getFeedbackOnHomeReceipe(std::vector<std::string> itemName);
    private:
    RecommendationService *recommendationService;
    SelectionService *selectionService;
    NotificationService *notificationService;
    MenuService *menuService;
};
#include "../inc/RecommendationEngine.h"
#pragma once
class ChefController
{
  public:
  int sessionId;
    RecommendationEngine recommendationEngine;
    ChefController(int sessionId);
    void rollOutNextDayMenu(std::vector<std::string>);
    std::vector<std::string> getRecommededMenu(std::string mealType);
    void loginChef();
    void performChefAction();
    void showRecommendations(std::string mealType);
    void getSelectedMenu();
    std::vector<std::string> selectedMenu;
};
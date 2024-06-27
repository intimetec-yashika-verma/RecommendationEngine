#include "ChefController.h"
#include "RecommendationEngine.h"
#include "NotificationService.h"
#include "Server.h"
#include "SelectionService.h"

std::vector<std::string> ChefController::getRecommededMenu(std::string mealType)
{
    RecommendationEngine recommendationEngine = RecommendationEngine();
    std::vector<std::string> topFoodItems = recommendationEngine.recommendTopFoodItems(mealType);
    return topFoodItems;
}
ChefController::ChefController(int sessionId)
{
    this->sessionId = sessionId;
}

void ChefController::loginChef()
{
    std::vector<std::string> user;
    user.push_back("2");
    Server::sendMessage(user, sessionId);

    performChefAction();
}

void ChefController::performChefAction()
{
    bool flag = true;
    while (flag)
    {
        std::vector<std::string> chefChoice = Server::receiveMessage(sessionId);
        if (chefChoice[0] == "1")
        {
            showRecommendations(chefChoice[1]);
            // getSelectedMenu();
        }
        else if (chefChoice[0] == "2")
        {
            publishTodaysMenu();
            // updateMenuItem(adminChoice);
        }
        else if (chefChoice[0] == "3")
        {
            // std::cout<<"deleteItem"<<std::endl;
            // deleteItemFromMenu(adminChoice);
        }
        else if (chefChoice[0] == "4")
        {
            //    viewMenuItems();
        }
    }
}

void ChefController::showRecommendations(std::string mealType)
{
    std::vector<std::string> menu = getRecommededMenu(mealType);
    Server::sendMessage(menu, sessionId);
    getSelectedMenu();
}

void ChefController::getSelectedMenu()
{
    std::vector<std::string> chefChoice = Server::receiveMessage(sessionId);
    SelectionService selectionService = SelectionService();
    selectionService.addSelectedItems(chefChoice);
    rollOutNextDayMenu(chefChoice);
}

void ChefController::rollOutNextDayMenu(std::vector<std::string> chefChoice)
{
    NotificationService notificationService = NotificationService();
    std::string notificationMessage = "Please vote for the item you would like to have";
    notificationService.sendNewNotification(0,"Select for tomorrow's menu");
}

void ChefController::publishTodaysMenu()
{
    SelectionService selectionService = SelectionService();
    std::vector<std::string> votedList = selectionService.getVotedItemsList();
    Server::sendMessage(votedList, sessionId);
    std::vector<std::string> chefChoice = Server::receiveMessage(sessionId);
    
}
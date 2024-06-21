#include "../inc/ChefController.h"
#include "../inc/RecommendationEngine.h"
#include "../inc/NotificationService.h"
#include "../inc/Server.h"
#include "../inc/SelectionService.h"

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
    std::cout<<chefChoice[0]<<std::endl;
    std::cout<<chefChoice[1]<<std::endl;
    SelectionService selectionService = SelectionService();
    selectionService.addSelectedItems(chefChoice);
    rollOutNextDayMenu(chefChoice);
}

void ChefController::rollOutNextDayMenu(std::vector<std::string> chefChoice)
{
    NotificationService notificationService = NotificationService();
    std::string notificationMessage = "Please vote for the item you would like to have as";
    notificationService.sendNewNotification(notificationMessage, "1", selectedMenu);
}
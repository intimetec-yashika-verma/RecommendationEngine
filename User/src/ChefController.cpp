#include "ChefController.h"
#include "RecommendationService.h"
#include "NotificationService.h"
#include "Server.h"
#include "SelectionService.h"
#include "Operation.h"

ChefController::ChefController(RecommendationService *recommendationService, SelectionService *selectionService, NotificationService *notificationService, MenuService *menuService) : recommendationService(recommendationService), selectionService(selectionService), notificationService(notificationService), menuService(menuService)
{
}
std::vector<std::string> ChefController::getRecommededMenu(std::string mealType)
{
  
    std::vector<std::string> topFoodItems = recommendationService->recommendTopFoodItems (mealType);
   
    return topFoodItems;
}

std::vector<std::string> ChefController::handleRequest(std::pair<Operation, std::vector<std::string>> request)
{
    std::vector<std::string> response;
    switch (request.first)
    {
    case GetRecommandationFromEngine:
    {
        std::cout << "GetRecommandationFromEngine" << std::endl;
        response = showRecommendations(request.second);
        break;
    }
    case SelectMenuForNextDay:
    {
        std::cout << "SelectMenuForNextDay" << std::endl;
        response = getSelectedMenu(request.second);
        break;
    }
    case GetVoteCountList:
    {
        response = getVotedItemsList();
        break;
    }
    case PublishMenuForToday:
    {
        response = publishTodaysMenu(request.second);
        break;
    }
    case discardMenuItem:
    {
        response = getDiscardedMenuItemsList();
        break;
    }
    case getHomeReceipe:
    {
        response = getFeedbackOnHomeReceipe(request.second);
        break;
    }    
        return response;
    }

}

std::vector<std::string> ChefController::showRecommendations(std::vector<std::string> mealType)
{
    std::vector<std::string> menu = getRecommededMenu(mealType[1]);
    for (int i = 0; i < menu.size(); i++)
    {
        std::cout << menu[i] << " ";
    }
    std::cout << std::endl;
    return menu;
}

std::vector<std::string> ChefController::getSelectedMenu(std::vector<std::string> selectedItems)
{
    std::vector<std::string> ItemsIdList;
    std::cout << selectedItems[0] << " " << selectedItems[1] << std::endl;
    for (int i = 1; i < selectedItems.size(); i++)
    {
        std::cout << selectedItems[i] << " " << std::endl;
        ItemsIdList.push_back(menuService->getMenuItemIdFromName(selectedItems[i]));
    }
    selectionService->addSelectedItems(ItemsIdList);
    std::cout << "Selection list filled" << std::endl;
    std::string notificationMessage = "Please vote for the item you would like to have";
    notificationService->sendNewNotification(3, "Select menu");
    std::string success = "got the selected menu";
    std::cout << success << std::endl;
    std::vector<std::string> response = {success};
    return response;
}

std::vector<std::string> ChefController::publishTodaysMenu(std::vector<std::string> finalizedmenu)
{
    std::vector<std::string> itemsNameList;
    for (int i = 1; i < finalizedmenu.size(); i++)
    {
        std::cout << finalizedmenu[i] << std::endl;
        itemsNameList.push_back(menuService->getMenuItemIdFromName(finalizedmenu[i]));
    }
    selectionService->addPublishedMenu(itemsNameList);
    return itemsNameList;
}

std::vector<std::string> ChefController::getVotedItemsList()
{
    std::vector<std::string> itemsList = selectionService->getVotedItemsList();
    return itemsList;
}

std::vector<std::string> ChefController::getDiscardedMenuItemsList()
{
     return recommendationService->generateDiscardList();
}

std::vector<std::string> ChefController::getFeedbackOnHomeReceipe(std::vector<std::string> itemName)
{
    std::string notificationMessage = "Please vote for the item you would like to have";
    notificationService->sendNewNotification(4, "Give feedback on discarded item");
    std::string success = "added feedback on home receipe";
    std::cout << success << std::endl;
    std::vector<std::string> response = {success};
    return response;
}
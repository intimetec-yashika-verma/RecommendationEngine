#include "ChefController.h"
#include "RecommendationEngine.h"
#include "NotificationService.h"
#include "Server.h"
#include "SelectionService.h"
#include "Operation.h"
#include "ItemReview.h"
#include "UserActivityService.h"
#include "PublishMenuService.h"

ChefController::ChefController(RecommendationEngine *recommendationEngine, SelectionService *selectionService,MenuService *menuService, FeedbackService *feedbackService, PublishMenuService *publishMenuService, DiscardMenuItemService *discardMenuItemService, UserProfile userProfile) : recommendationEngine(recommendationEngine), selectionService(selectionService), notificationService(notificationService), menuService(menuService), feedbackService(feedbackService), publishMenuService(publishMenuService), discardMenuItemService(discardMenuItemService), userProfile(userProfile)
{
    helper = new Helper();
}

std::string ChefController::handleRequest(std::pair<Operation, std::string> request)
{
    std::string response;
    switch (request.first)
    {
    case getRecommandationFromEngine:
    {
        response = showRecommendations(request.second);
        break;
    }
    case selectMenuForNextDay:
    {
        response = getSelectedMenu(request.second);
        break;
    }
    case getVoteCountList:
    {
        response = getVotedItemsList(request.second);
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
        response = getFeedbackOrHomeReceipe(request.second);
        break;
    }
    }
    return response;
}

std::vector<ItemReview> ChefController::getRecommendedMenu(std::string mealType)
{
    std::unordered_map<std::string, std::vector<Feedback>> feedbackMap = feedbackService->itemFeedbacks();
    std::vector<MenuItem> menuItems = menuService->getMenuItem();
    std::vector<ItemReview> topFoodItems = recommendationEngine->recommendTopFoodItems(mealType, feedbackMap, menuItems);
    recommendedMenu = topFoodItems;
    return topFoodItems;
}

std::string ChefController::showRecommendations(std::string mealType)
{
    std::vector<ItemReview> menu = getRecommendedMenu(mealType);
    std::string menuListCommaSeprated = helper->serializeItemReview(menu);
    return menuListCommaSeprated;
}

std::string ChefController::getSelectedMenu(std::string userResponse)
{
    std::vector<std::string> selectedItems = helper->deserialize(userResponse);
    selectionService->addSelectedItems(userProfile.userId,selectedItems,recommendedMenu);
    std::string success = "got the selected menu";
    return success;
}

std::string ChefController::publishTodaysMenu(std::string finalizedmenu)
{
    std::vector<std::string> itemsNameList = helper->deserialize(finalizedmenu);
    publishMenuService->addPublishedMenu(itemsNameList);
    return "Published menu for today";
}

std::string ChefController::getVotedItemsList(std::string mealType)
{
    std::vector<VoteCount> itemsList = selectionService->getVotedItemsList(mealType);
    std::string itemsListCommaSeprated = helper->serializeVoteCount(itemsList);
    return itemsListCommaSeprated;
}

std::string ChefController::getDiscardedMenuItemsList()
{
    std::unordered_map<std::string, std::vector<Feedback>> feedbackMap = feedbackService->itemFeedbacks();
    std::vector<MenuItem> menuItems = menuService->getMenuItem();
    std::vector<ItemReview> item = recommendationEngine->generateDiscardList(feedbackMap, menuItems);
    for (int i = 0; i < item.size(); i++)
    {
        std::string sentiments = helper->serialize(item[i].sentiments);
        discardMenuItemService->addDiscardedItem(item[i].itemName, std::to_string(item[i].averageRating), sentiments);
    }
    std::string discardedItems = helper->serializeItemReview(item);
    return discardedItems;
}

std::string ChefController::getFeedbackOrHomeReceipe(std::string itemName)
{
    notificationService->sendNewNotification(userProfile.userId,"Give feedback on discarded item" + itemName);
    std::string success = "Notification sent to user";
    return success;
}

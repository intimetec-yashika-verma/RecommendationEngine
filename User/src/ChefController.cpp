#include "ChefController.h"
#include "RecommendationService.h"
#include "NotificationService.h"
#include "Server.h"
#include "SelectionService.h"
#include "Operation.h"
#include "ItemReview.h"
#include "RequestSerializer.h"
#include "StringSerializer.h"
#include "UserActivityService.h"
#include "PublishMenuService.h"

ChefController::ChefController(RecommendationService *recommendationService, SelectionService *selectionService, NotificationService *notificationService, MenuService *menuService, FeedbackService *feedbackService, PublishMenuService *publishMenuService,UserActivityService *userActivityService, DiscardMenuItemService *discardMenuItemService, UserProfile userProfile) : recommendationService(recommendationService), selectionService(selectionService), notificationService(notificationService), menuService(menuService), feedbackService(feedbackService), publishMenuService(publishMenuService), discardMenuItemService(discardMenuItemService), userProfile(userProfile)
{
}
std::vector<ItemReview> ChefController::getRecommendedMenu(std::string mealType)
{
    std::unordered_map<std::string, std::vector<Feedback>> feedbackMap = feedbackService->itemFeedbacks();
    std::vector<MenuItem> menuItems = menuService->getMenuItem();
    std::vector<ItemReview> topFoodItems = recommendationService->recommendTopFoodItems(mealType, feedbackMap, menuItems);

    return topFoodItems;
}

std::string ChefController::handleRequest(std::pair<Operation, std::string> request)
{
    std::string response;
    switch (request.first)
    {
    case getRecommandationFromEngine:
    {
        std::cout << "GetRecommandationFromEngine" << std::endl;
        response = showRecommendations(request.second);
        break;
    }
    case selectMenuForNextDay:
    {
        std::cout << "SelectMenuForNextDay" << std::endl;
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
        return response;
    }
}

std::string ChefController::showRecommendations(std::string mealType)
{
    std::vector<ItemReview> menu = getRecommendedMenu(mealType);
    std::string menuListCommaSeprated = RequestSerializer::serializeItemReview(menu);
    return menuListCommaSeprated;
}

std::string ChefController::getSelectedMenu(std::string userResponse)
{
    std::vector<std::string> selectedItems = StringSerializer::deserialize(userResponse);
    std::cout << selectedItems[0] << " " << selectedItems[1] << std::endl;
    selectionService->addSelectedItems(selectedItems);
    std::cout << "Selection list filled" << std::endl;
    std::string avtivity = "selected items for" + selectedItems[0];
    userActivityService->saveUserActivity(userProfile.userId, avtivity);
    std::string notificationMessage = "Please vote for the item you would like to have as " + selectedItems[0];
    notificationService->sendNewNotification(notificationMessage);
    std::string success = "got the selected menu";
    std::cout << success << std::endl;
    return success;
}

std::string ChefController::publishTodaysMenu(std::string finalizedmenu)
{
    std::vector<std::string> itemsNameList = StringSerializer::deserialize(finalizedmenu);
    publishMenuService->addPublishedMenu(itemsNameList);
}

std::string ChefController::getVotedItemsList(std::string mealType)
{
    std::vector<VoteCount> itemsList = selectionService->getVotedItemsList(mealType);
    std::string itemsListCommaSeprated = RequestSerializer::serializeVoteCount(itemsList);
    return itemsListCommaSeprated;
}

std::string ChefController::getDiscardedMenuItemsList()
{
    std::unordered_map<std::string, std::vector<Feedback>> feedbackMap = feedbackService->itemFeedbacks();
    std::vector<MenuItem> menuItems = menuService->getMenuItem();
    std::vector<ItemReview> item = recommendationService->generateDiscardList(feedbackMap, menuItems);
    for (int i = 0; i < item.size(); i++)
    {
        std::string sentiments = StringSerializer::serialize(item[i].sentiments);
        discardMenuItemService->addDiscardedItem(item[i].itemName, std::to_string(item[i].averageRating),sentiments);
    }

    std::string discardedItems = RequestSerializer::serializeItemReview(item);
    return discardedItems;
}

std::string ChefController::getFeedbackOrHomeReceipe(std::string itemName)
{
    notificationService->sendNewNotification("Give feedback on discarded item" + itemName);
    std::string success = "added feedback on home receipe";
    std::cout << success << std::endl;
    return success;
}
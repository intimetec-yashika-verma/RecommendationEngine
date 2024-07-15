#include "ChefController.h"
#include "RecommendationService.h"
#include "NotificationService.h"
#include "Server.h"
#include "SelectionService.h"
#include "Operation.h"
#include "ItemReview.h"

#include "UserActivityService.h"
#include "PublishMenuService.h"

ChefController::ChefController(RecommendationService *recommendationService, SelectionService *selectionService, NotificationService *notificationService, MenuService *menuService, FeedbackService *feedbackService, PublishMenuService *publishMenuService, UserActivityService *userActivityService, DiscardMenuItemService *discardMenuItemService, UserProfile userProfile) : recommendationService(recommendationService), selectionService(selectionService), notificationService(notificationService), menuService(menuService), feedbackService(feedbackService), publishMenuService(publishMenuService), discardMenuItemService(discardMenuItemService), userProfile(userProfile)
{
    helper = new Helper();
}
std::vector<ItemReview> ChefController::getRecommendedMenu(std::string mealType)
{
    std::unordered_map<std::string, std::vector<Feedback>> feedbackMap = feedbackService->itemFeedbacks();
    std::vector<MenuItem> menuItems = menuService->getMenuItem();
    std::vector<ItemReview> topFoodItems = recommendationService->recommendTopFoodItems(mealType, feedbackMap, menuItems);
    recommendedMenu = topFoodItems;
    return topFoodItems;
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

std::string ChefController::showRecommendations(std::string mealType)
{
    std::vector<ItemReview> menu = getRecommendedMenu(mealType);
    for (int i = 0; i < menu.size(); i++)
    {
        std::cout << menu[i].itemName << " " << menu[i].averageRating << std::endl;
    }
    std::string menuListCommaSeprated = helper->serializeItemReview(menu);
    std::cout << menuListCommaSeprated << std::endl;
    return menuListCommaSeprated;
}

std::string ChefController::getSelectedMenu(std::string userResponse)
{
    std::vector<std::string> selectedItems = helper->deserialize(userResponse);
    for (int i = 1; i < selectedItems.size(); i++)
    {
        for (int j = 0; j < recommendedMenu.size(); j++)
        {
            if (selectedItems[i] == recommendedMenu[j].itemName)
            {
                selectionService->addSelectedItems(selectedItems[i], std::to_string(recommendedMenu[j].averageRating), helper->serialize(recommendedMenu[j].sentiments));
            }
        }
    }
    addNotification("Vote for tommorow " + selectedItems[0]);
    std::string success = "got the selected menu";
    std::cout << success << std::endl;
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
    std::vector<ItemReview> item = recommendationService->generateDiscardList(feedbackMap, menuItems);
    for (int i = 0; i < item.size(); i++)
    {
        std::string sentiments = helper->serialize(item[i].sentiments);
        discardMenuItemService->addDiscardedItem(item[i].itemName, std::to_string(item[i].averageRating), sentiments);
    }

    std::string discardedItems = helper->serializeItemReview(item);
    std::cout << discardedItems << std::endl;
    return discardedItems;
}

std::string ChefController::getFeedbackOrHomeReceipe(std::string itemName)
{
    notificationService->sendNewNotification("Give feedback on discarded item" + itemName);
    std::string success = "added feedback on home receipe";
    std::cout << success << std::endl;
    addUserActivity("Asked for feedback on Discarded Items");
    addNotification("Provide feedback on discarded Item " + itemName);
    return success;
}

void ChefController::addUserActivity(std::string message)
{
    userActivityService->saveUserActivity(userProfile.userId, message);
}

void ChefController::addNotification(std::string message)
{
    std::cout << "Sent notification" << std::endl;
    notificationService->sendNewNotification(message);
}
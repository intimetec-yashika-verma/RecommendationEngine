#include <vector>
#include <iostream>
#include "EmployeeController.h"
#include "NotificationService.h"
#include "SelectionService.h"
#include "FeedbackService.h"
#include "Server.h"
#include "UserProfile.h"
#include "RecommendationEngine.h"
#include "DiscardedItemReview.h"
#include "UserActivityService.h"

EmployeeController::EmployeeController(NotificationService *notificationService, SelectionService *selectionService, FeedbackService *feedbackService, RecommendationEngine *recommendationEngine, MenuService *menuService, PublishMenuService *publishMenuService, DiscardMenuItemService *discardMenuItemService, UserActivityService *userActivityService, UserProfile userProfile) : notificationService(notificationService), selectionService(selectionService), feedbackService(feedbackService), recommendationEngine(recommendationEngine), menuService(menuService), publishMenuService(publishMenuService), discardMenuItemService(discardMenuItemService), userActivityService(userActivityService), userProfile(userProfile)
{
    helper = new Helper();
}

std::string EmployeeController::handleRequest(std::pair<Operation, std::string> request)
{
    std::string response;
    switch (request.first)
    {
    case viewNotification:
    {
        response = showNotifications();
        break;
    }
    case voteItemFromTomorrowMenu:
    {
        response = voteForTomorrowMenu(request.second);
        break;
    }
    case saveVotingResponse:
    {
        response = getVotedItems(request.second);
        break;
    }
    case provideFeedback:
    {
        response = getItemsListForFeedback();
        break;
    }
    case saveFeedback:
    {
        response = getUserFeedback(request.second);
        break;
    }
    case getDiscardedMenuItemsList:
    {
        response = getDiscardedMenuItems();
        break;
    }
    case Operation::getFeedbackOnDiscardedItem:
    {
        response = getFeedbackOnDiscardedItem(request.second);
        break;
    }
    }
    return response;
}

std::string EmployeeController::showNotifications()
{
    std::vector<std::string> notifications = notificationService->getAllNotifications(userProfile.userId);
    std::string notificationsCommaSeprated = helper->serialize(notifications);
    return notificationsCommaSeprated;
}

std::string EmployeeController::voteForTomorrowMenu(std::string mealType)
{
    std::vector<MenuItem> selectedItemsList = selectionService->getListOfItemsToVoteForMealType(mealType);
    std::vector<MenuItem> menuItemsList = menuService->getMenuItem();
    std::vector<MenuItem> items = recommendationEngine->sortRecommendedMenuItemsBasedOnProfile(userProfile, selectedItemsList, menuItemsList);
    std::vector<ItemReview> itemReview = selectionService->getSelectedItemsReview();
    std::vector<ItemReview> sortedItems;
    for (int i = 0; i < items.size(); i++)
    {
        for (int j = 0; j < itemReview.size(); j++)
        {
            if (items[i].itemName == itemReview[j].itemName)
            {
                sortedItems.push_back(itemReview[j]);
            }
        }
    }
    for(int i=0;i<sortedItems.size();i++)
    {
        std::cout<<"yashika "<<sortedItems[i].itemName<<std::endl;
    }
    std::string itemReviewCommaSeprated = helper->serializeItemReview(sortedItems);
    return itemReviewCommaSeprated;
}

std::string EmployeeController::getVotedItems(std::string itemsList)
{
    std::vector<std::string> votedItems = helper->deserialize(itemsList);
    selectionService->saveVotes(userProfile.userId,votedItems);
    return "voting saved";
}

std::string EmployeeController::getItemsListForFeedback()
{
    std::vector<std::string> itemsList = publishMenuService->getPublishedMenu();
    std::string itemsListCommaSeprated = helper->serialize(itemsList);
    std::cout<<itemsListCommaSeprated<<std::endl;
    return itemsListCommaSeprated;
}

std::string EmployeeController::getUserFeedback(std::string response)
{
    std::unordered_map<std::string, Feedback> feedback = helper->deserializeFeedbacks(response);
    feedbackService->addItemFeedback(userProfile.userId, feedback);
    return response;
}

std::string EmployeeController::getDiscardedMenuItems()
{
    std::vector<ItemReview> discardedItems = discardMenuItemService->getDiscardedItems();
    std::string discardedItemsCommaSeprated = helper->serializeItemReview(discardedItems);
    return discardedItemsCommaSeprated;
}

std::string EmployeeController::getFeedbackOnDiscardedItem(std::string feedback)
{
    DiscardedItemReview itemReview = helper->deserializeDiscardedItemReview(feedback);
    feedbackService->addFeedbackOnDiscaredItem(userProfile.userId, itemReview.itemName, itemReview.negativePointOnItem, itemReview.improvementPointOnItem, itemReview.homeRecepie);
    return "feedback added";
}

#include <vector>
#include <iostream>
#include "EmployeeController.h"
#include "NotificationService.h"
#include "SelectionService.h"
#include "FeedbackService.h"
#include "Server.h"
#include "UserProfile.h"
#include "StringSerializer.h"
#include "RecommendationService.h"
#include "RequestSerializer.h"
#include "DiscardedItemReview.h"


EmployeeController::EmployeeController(NotificationService *notificationService, SelectionService *selectionService, FeedbackService *feedbackService,RecommendationService *recommendationService,MenuService *menuService,PublishMenuService *publishMenuService,DiscardMenuItemService *discardMenuItemService, UserProfile userProfile) : notificationService(notificationService), selectionService(selectionService), feedbackService(feedbackService),recommendationService(recommendationService),menuService(menuService),publishMenuService(publishMenuService), discardMenuItemService(discardMenuItemService), userProfile(userProfile)
{
}

std::string EmployeeController::handleRequest(std::pair<Operation, std::string> request)
{
    std::string response;
    switch (request.first)
    {
    case viewNotification:
    {
        std::cout << "ViewNotification" << std::endl;
        response = showNotifications();
        break;
    }
    case voteItemFromTomorrowMenu:
    {
        std::cout << "VoteItemFromTomorrowMenu" << std::endl;
        response = voteForTomorrowMenu(request.second);
        break;
    }
    case saveVotingResponse:
    {
        std::cout << "SaveVotingResponse" << std::endl;
        response = getVotedItems(request.second);
        break;
    }
    case provideFeedback:
    {
        std::cout << "ProvideFeedback" << std::endl;
        response = getItemsListForFeedback();
        break;
    }
    case saveFeedback:
    {
        std::cout << "saveFeedback" << std::endl;
        response = getUserFeedback(request.second);
        break;
    }
    case getDiscardedMenuItemsList:
    {
        std::cout << "GetDiscardedItems" << std::endl;
        response = getDiscardedMenuItems();
        break;
    }
    case Operation::getFeedbackOnDiscardedItem:
    {
        std::cout << "GetFeedbackOnDiscardedItem" << std::endl;
        response = getFeedbackOnDiscardedItem(request.second);
        break;
    }
    return response;
}
}

std::string EmployeeController::showNotifications()
{
    std::vector<std::string> notifications = notificationService->getAllNotifications(userProfile.userId);
    for(int i=0;i<notifications.size();i++)
    {
        std::cout<<notifications[i]<<std::endl;
    }
    std::string notificationsCommaSeprated = StringSerializer::serialize(notifications);
    return notificationsCommaSeprated;
}

std::string EmployeeController::voteForTomorrowMenu(std::string mealType)
{
    std::vector<MenuItem> selectedItemsList = selectionService->getListOfItemsToVoteForMealType(mealType);
    std::vector<MenuItem> menuItemsList = menuService->getMenuItem();
    std::vector<MenuItem> itemReview  =  recommendationService->sortRecommendedMenuItemsBasedOnProfile(userProfile,selectedItemsList,menuItemsList);
    std::string itemReviewCommaSeprated = RequestSerializer::serializeMenuItems(itemReview);
    return itemReviewCommaSeprated;
}

std::string EmployeeController::getVotedItems(std::string itemsList)
{
    std::vector<std::string> votedItems = StringSerializer::deserialize(itemsList);
    selectionService->saveVotes(votedItems);
    return "";
}

std::string EmployeeController::getItemsListForFeedback()
{
    std::vector<std::string> itemsList = publishMenuService->getPublishedMenu();
    std::string itemsListCommaSeprated = StringSerializer::serialize(itemsList);
    return itemsListCommaSeprated;
}

std::string EmployeeController::getUserFeedback(std::string response)
{
    std::unordered_map<std::string,Feedback> feedback = RequestSerializer::deserializeFeedbacks(response);
    for(int i=0;i<response.size();i++)
    {
        std::cout<<response[i]<<std::endl;
    }

     feedbackService->addItemFeedback(userProfile.userId,feedback);
     return response;
}

std::string EmployeeController::getDiscardedMenuItems()
{
    std::vector<ItemReview> discardedItems = discardMenuItemService->getDiscardedItems();
    std::string discardedItemsCommaSeprated = RequestSerializer::serializeItemReview(discardedItems);
    return discardedItemsCommaSeprated;
}

std::string EmployeeController::getFeedbackOnDiscardedItem(std::string feedback)
{
    DiscardedItemReview itemReview = RequestSerializer::deserializeDiscardedItemReview(feedback);
    feedbackService->addFeedbackOnDiscaredItem(userProfile.userId,itemReview.itemName,itemReview.negativePointOnItem,itemReview.improvementPointOnItem,itemReview.homeRecepie);
    return "feedback";
}


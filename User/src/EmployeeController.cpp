#include "EmployeeController.h"
#include "NotificationService.h"
#include "SelectionService.h"
#include "FeedbackService.h"
#include "Server.h"
#include <vector>
#include <iostream>

EmployeeController::EmployeeController(NotificationService *notificationService, SelectionService *selectionService, FeedbackService *feedbackService,std::string userId) : notificationService(notificationService), selectionService(selectionService), feedbackService(feedbackService),userId(userId)
{
}

std::vector<std::string> EmployeeController::handleRequest(std::pair<Operation, std::vector<std::string>> request)
{
    std::vector<std::string> response;
    switch (request.first)
    {
    case ViewNotification:
    {
        std::cout << "ViewNotification" << std::endl;
        response = showNotifications();
        break;
    }
    case VoteItemFromTomorrowMenu:
    {
        std::cout << "VoteItemFromTomorrowMenu" << std::endl;
        response = voteForTomorrowMenu();
        break;
    }
    case SaveVotingResponse:
    {
        std::cout << "SaveVotingResponse" << std::endl;
        response = getVottedItems(request.second);
        break;
    }
    case ProvideFeedback:
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
    }
    return response;
}

std::vector<std::string> EmployeeController::showNotifications()
{
    std::vector<std::string> notifications = notificationService->getAllNotifications(userId);
    for(int i=0;i<notifications.size();i++)
    {
        std::cout<<notifications[i]<<std::endl;
    }
    return notifications;
}

std::vector<std::string> EmployeeController::voteForTomorrowMenu()
{
    std::vector<MenuItem> menuItems = selectionService->getListOfItemsToVote();
     
    return menuItems;
}

std::vector<std::string> EmployeeController::getVottedItems(std::vector<std::string> itemsList)
{
    std::vector<std::string> subVector(itemsList.begin() + 1, itemsList.end());
    selectionService->saveVotes(subVector);
    return subVector;
}

std::vector<std::string> EmployeeController::getItemsListForFeedback()
{
    std::vector<std::string> itemsList = selectionService->getPublishedMenu();
    return itemsList;
}

std::vector<std::string> EmployeeController::getUserFeedback(std::vector<std::string> response)
{
    for(int i=0;i<response.size();i++)
    {
        std::cout<<response[i]<<std::endl;
    }
     feedbackService->addItemFeedback(response);
     return response;
}


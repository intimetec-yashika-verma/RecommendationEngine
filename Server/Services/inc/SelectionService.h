#pragma once
#include <iostream>
#include <vector>
#include "SelectedItemsDAO.h"
#include "PublishedMenuDAO.h"
#include "VoteCount.h"
#include "ItemReview.h"
#include "NotificationService.h"
#include "UserActivityService.h"
class SelectionService
{

public:
    SelectionService(SelectedItemsDAO *selectedItemsDAO,NotificationService *notificationService,UserActivityService *userActivityService);
    void addSelectedItems(std::string userId,std::vector<std::string> selectedItems, std::vector<ItemReview> recommendedMenu);
    std::vector<VoteCount> getVotedItemsList(std::string mealType);
    std::vector<MenuItem> getListOfItemsToVote();
    void saveVotes(std::string userId,std::vector<std::string> votedItems);
    std::vector<MenuItem> getListOfItemsToVoteForMealType(std::string mealType);
    std::vector<std::string> getPublishedMenu();
    std::vector<ItemReview> getSelectedItemsReview();

private:
    SelectedItemsDAO *selectedItemsDAO;
    NotificationService *notificationService;
    UserActivityService *userActivityService;
    Helper* helper;
};
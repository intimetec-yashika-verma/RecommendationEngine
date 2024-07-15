#pragma once
#include <iostream>
#include <vector>
#include "SelectedItemsDAO.h"
#include "PublishedMenuDAO.h"
#include "VoteCount.h"
#include "ItemReview.h"
class SelectionService
{

public:
    SelectionService(SelectedItemsDAO *selectedItemsDAO);
    void addSelectedItems(std::string itemsList, std::string rating, std::string comment);
    std::vector<VoteCount> getVotedItemsList(std::string mealType);
    std::vector<MenuItem> getListOfItemsToVote();
    void saveVotes(std::vector<std::string> votedItems);
    std::vector<MenuItem> getListOfItemsToVoteForMealType(std::string mealType);
    std::vector<std::string> getPublishedMenu();
    std::vector<ItemReview> getSelectedItemsReview();

private:
    SelectedItemsDAO *selectedItemsDAO;
};
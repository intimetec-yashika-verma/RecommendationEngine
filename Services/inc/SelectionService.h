#pragma once
#include <iostream>
#include <vector>
#include "SelectedItemsDAO.h"
#include "PublishedMenuDAO.h"
#include "VoteCount.h"
class SelectionService
{

public:
    SelectionService(SelectedItemsDAO *selectedItemsDAO);
    void addSelectedItems(std::vector<std::string> itemsList);
    std::vector<VoteCount> getVotedItemsList(std::string mealType);
    std::vector<MenuItem> getListOfItemsToVote();
    void saveVotes(std::vector<std::string> votedItems);
    std::vector<MenuItem> getListOfItemsToVoteForMealType(std::string mealType);
    std::vector<std::string> getPublishedMenu();

private:
    SelectedItemsDAO *selectedItemsDAO;
};
#include "SelectionService.h"
#include "SelectedItemsDAO.h"
#include "MenuService.h"
#include "PublishedMenuDAO.h"
#include "VoteCount.h"

SelectionService::SelectionService(SelectedItemsDAO *selectedItemsDAO) : selectedItemsDAO(selectedItemsDAO)
{
}
void SelectionService::addSelectedItems(std::string item, std::string rating, std::string comment)
{
    selectedItemsDAO->addSlectedItems(item, rating, comment);
}

std::vector<VoteCount> SelectionService::getVotedItemsList(std::string mealType)
{
    std::vector<VoteCount> itemsList = selectedItemsDAO->getSelectedItemsAndVotes(mealType);
    return itemsList;
}

std::vector<MenuItem> SelectionService::getListOfItemsToVote()
{
    return selectedItemsDAO->getSelectedItems();
}

void SelectionService::saveVotes(std::vector<std::string> votedItems)
{
    for (int i = 0; i < votedItems.size(); i++)
    {
        std::cout << votedItems[i] << std::endl;
        selectedItemsDAO->saveUserVotes(votedItems[i]);
    }
}

std::vector<MenuItem> SelectionService::getListOfItemsToVoteForMealType(std::string mealType)
{
    return selectedItemsDAO->getSelectedItemForMealType(mealType);
}

std::vector<ItemReview> SelectionService::getSelectedItemsReview()
{
    return selectedItemsDAO->getSelectedItemsReview();
}
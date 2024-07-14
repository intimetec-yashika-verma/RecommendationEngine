#include "SelectionService.h"
#include "SelectedItemsDAO.h"
#include "MenuService.h"
#include "PublishedMenuDAO.h"
#include "VoteCount.h" 

SelectionService::SelectionService(SelectedItemsDAO *selectedItemsDAO) : selectedItemsDAO(selectedItemsDAO)
{
}
void SelectionService::addSelectedItems(std::vector<std::string> itemsList)
{
    std::cout << itemsList.size() << std::endl;
    for (int i = 1; i < itemsList.size(); i++)
    {
        selectedItemsDAO->addSlectedItems(itemsList[i]);
    }    
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
    for(int i =0;i<votedItems.size();i++)
    {
        std::cout<<votedItems[i]<<std::endl;
        selectedItemsDAO->saveUserVotes(votedItems[i]);
    }
}

std::vector<MenuItem> SelectionService::getListOfItemsToVoteForMealType(std::string mealType)
{
    return selectedItemsDAO->getSelectedItemForMealType(mealType);
}
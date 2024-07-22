#include "SelectionService.h"
#include "SelectedItemsDAO.h"
#include "MenuService.h"
#include "PublishedMenuDAO.h"
#include "VoteCount.h"

SelectionService::SelectionService(SelectedItemsDAO *selectedItemsDAO,NotificationService *notificationService,UserActivityService *userActivityService) : selectedItemsDAO(selectedItemsDAO)
{
    helper = new Helper();
}
void SelectionService::addSelectedItems(std::string userId,std::vector<std::string> selectedItems, std::vector<ItemReview> recommendedMenu)
{ for (int i = 1; i < selectedItems.size(); i++)
    {
        for (int j = 0; j < recommendedMenu.size(); j++)
        {
            if (selectedItems[i] == recommendedMenu[j].itemName)
            {
                selectedItemsDAO->addSlectedItems(selectedItems[i], std::to_string(recommendedMenu[j].averageRating), helper->serialize(recommendedMenu[j].sentiments));
            }
        }
    }
    notificationService->sendNewNotification(userId,"Vote for tommorow " + selectedItems[0]);
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

void SelectionService::saveVotes(std::string userId,std::vector<std::string> votedItems)
{
    for (int i = 0; i < votedItems.size(); i++)
    {
        std::cout << votedItems[i] << std::endl;
        selectedItemsDAO->saveUserVotes(votedItems[i]);
    }
    userActivityService->saveUserActivity(userId,"Voted for Items");
}

std::vector<MenuItem> SelectionService::getListOfItemsToVoteForMealType(std::string mealType)
{
    return selectedItemsDAO->getSelectedItemForMealType(mealType);
}

std::vector<ItemReview> SelectionService::getSelectedItemsReview()
{
    return selectedItemsDAO->getSelectedItemsReview();
}
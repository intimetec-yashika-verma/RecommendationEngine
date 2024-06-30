#include "SelectionService.h"
#include "SelectedItemsDAO.h"
#include "MenuService.h"
#include "PublishedMenuDAO.h"

SelectionService::SelectionService(SelectedItemsDAO *selectedItemsDAO, PublishedMenuDAO *publishedMenuDAO) : selectedItemsDAO(selectedItemsDAO), publishedMenuDAO(publishedMenuDAO)
{
}
void SelectionService::addSelectedItems(std::vector<std::string> itemsList)
{
    std::cout << itemsList.size() << std::endl;
    for (int i = 0; i < itemsList.size(); i++)
    {
        selectedItemsDAO->addSlectedItems(itemsList[i]);
    }
}

std::vector<std::string> SelectionService::getVotedItemsList()
{
    std::vector<std::string> itemsList = selectedItemsDAO->getSelectedItems();
    return itemsList;
}

void SelectionService::addPublishedMenu(std::vector<std::string> itemsList)
{
    for(int i=0;i<itemsList.size();i++)
    {
       publishedMenuDAO->addItems(itemsList[i]);
    }
}

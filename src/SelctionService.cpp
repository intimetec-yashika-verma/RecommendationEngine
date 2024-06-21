#include "../inc/SelectionService.h"
#include "../inc/SelectedItemsDAO.h"
#include "../inc/MenuService.h"

void SelectionService::addSelectedItems(std::vector<std::string> itemsList )
{
    SelectedItemsDAO dao=SelectedItemsDAO();
    MenuService menuService = MenuService();
    std::cout<<itemsList.size()<<std::endl;
   for(int i=0;i<itemsList.size();i++)
   {
       std::cout<<itemsList[i]<<std::endl;
       std::string itemName =menuService.getMenuItemIdFromName(itemsList[i]);
       std::cout<<itemName<<std::endl;
       dao.addSlectedItems(itemName,itemsList[i]);
   }
}


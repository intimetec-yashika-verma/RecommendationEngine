#include "PublishMenuService.h"

PublishMenuService::PublishMenuService(PublishedMenuDAO *publishedMenuDAO):publishedMenuDAO(publishedMenuDAO)
{}
void PublishMenuService::addPublishedMenu(std::vector<std::string> itemsList)
{
   for(int i=0;i<itemsList.size();i++)
   {
    publishedMenuDAO->addItems(itemsList[i]);
   }
}

std::vector<std::string> PublishMenuService::getPublishedMenu()
{
   return publishedMenuDAO->getItems();
}
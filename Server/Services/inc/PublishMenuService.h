#pragma once
#include "PublishedMenuDAO.h"
class PublishMenuService
{
public:
    PublishMenuService(PublishedMenuDAO *publishedMenuDAO);
    void addPublishedMenu(std::vector<std::string> itemsList);
    std::vector<std::string> getPublishedMenu();

private:
    PublishedMenuDAO *publishedMenuDAO;
};
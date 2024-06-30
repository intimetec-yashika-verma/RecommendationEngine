#pragma once
#include <iostream>
#include <vector>
#include "SelectedItemsDAO.h"
#include "PublishedMenuDAO.h"
class SelectionService{
    
    public:
    SelectionService(SelectedItemsDAO *selectedItemsDAO, PublishedMenuDAO *publishedMenuDAO);
    void addSelectedItems(std::vector<std::string> itemsList);
    std::vector<std::string> getVotedItemsList();
    void addPublishedMenu(std::vector<std::string>  itemsList );
    private:
    SelectedItemsDAO *selectedItemsDAO;
    PublishedMenuDAO *publishedMenuDAO;
 };
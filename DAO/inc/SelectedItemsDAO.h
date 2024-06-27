#pragma once
#include <iostream>
#include <vector>

class SelectedItemsDAO{
    public:
    void addSlectedItems(std::string itemName,std::string itemId);
    std::vector<std::string> getSelectedItems();
};
#include "AdminInterface.h"
#include "Operation.h"
#include "MenuItem.h"
#include <limits>

AdminInterface::AdminInterface(Client *client) : client(client)
{
    helper = new Helper();
}

void AdminInterface::showUserMenuPrompt()
{
    std::cout << "Welcome Admin\n\n"
              << std::endl;
    bool flag = true;
    while (flag)
    {
        std::cout << "Select the operation which you like to perform\n"
                     "1. Add menu Item\n"
                     "2. Update menu Item\n"
                     "3. Delete Menu Item\n"
                     "4. View Menu\n"
                     "5. Logout\n"
                     "Enter your choice :- "
                  << std::endl;
        int adminChoice;
        std::cin >> adminChoice;
        switch (adminChoice)
        {
        case 1:
            showAddItemPrompt();
            break;
        case 2:
            showUpdateMenuPrompt();
            break;
        case 3:
            showDeleteItemPrompt();
            break;
        case 4:
            showMenu();
            break;
        case 5:
            logout();
            flag = false;
            break;
        default:
            std::cout << "Invalid Choice" << std::endl;
            break;
        }
    }
}

void AdminInterface::showAddItemPrompt()
{
    MenuItem itemData;
    std::cout << "Enter Item name:- " << std::endl;
    std::getline(std::cin >> std::ws, itemData.itemName);
    std::cout << "Enter Item availablity:- " << std::endl;
    std::getline(std::cin >> std::ws, itemData.availability);
    std::cout << "Enter Item price:- " << std::endl;
    std::getline(std::cin >> std::ws, itemData.price);
    std::cout << "Enter meal type(breakfast/lunch/dinner):- " << std::endl;
    std::getline(std::cin >> std::ws, itemData.mealType);
    std::cout << "Is it vegetarian, non-vegetarian or Eggetarian? " << std::endl;
    std::getline(std::cin >> std::ws, itemData.dietaryCategory);
    std::cout << "What it the spice level of it ?(High/Medium/Low) " << std::endl;
    std::getline(std::cin >> std::ws, itemData.spiceLevel);
    std::cout << "Enter the cuisine type:- " << std::endl;
    std::getline(std::cin >> std::ws, itemData.cuisineCategory);
    std::cout << "Is it a sweet dish? " << std::endl;
    std::getline(std::cin >> std::ws, itemData.sweet);
    std::string userInput = std::to_string(Operation::addMenuItem) + "$" + itemData.serialize();
    std::cout << "userInput " << userInput << std::endl;
    client->sendMessage(userInput);
    std::string serverResponse = client->receiveMessage();
    if (serverResponse == "Item added successfully")
    {
        std::cout << "Item added successfully" << std::endl;
    }
    else
    {
        std::cout << "Item not added" << std::endl;
    }
}

void AdminInterface::showUpdateMenuPrompt()
{

    std::string itemToUpdate;
    std::cout << "Name the item you like to update" << std::endl;
    std::cin >> itemToUpdate;
    std::string updatedData = getDataToUpdate(itemToUpdate);
    std::string userInput = std::to_string(Operation::updateMenuItem) + "$" + updatedData;
    client->sendMessage(userInput);
    std::string serverResponse = client->receiveMessage();
    if (serverResponse == "Item updated successfully")
    {
        std::cout << "Item updated successfully" << std::endl;
    }
    else
    {
        std::cout << "Item not updated" << std::endl;
    }
}

std::string AdminInterface::getDataToUpdate(std::string itemName)
{
    MenuItem itemData;
    bool flag = true;
    int userInput;
    itemData.itemName = itemName;
    while (flag)
    {
        std::cout << "Select value which you want to update\n"
                     "1. Availablity\n"
                     "2. Price\n"
                     "3. MealType\n"
                     "4. Vegetarian Preference\n"
                     "5. Spice level\n"
                     "6. Food Type\n"
                     "7. Sweet\n"
                     "8. Exit\n"
                     "Enter your choice:- ";
        std::cin >> userInput;
        switch (userInput)
        {
        case 1:
            std::cout << "Enter updated availablity:-" << std::endl;
            std::cin >> itemData.availability;
            break;
        case 2:
            std::cout << "Enter updated price:-" << std::endl;
            std::cin >> itemData.price;
            break;
        case 3:
            std::cout << "Enter updated mealType:-" << std::endl;
            std::cin >> itemData.mealType;
            break;
        case 4:
            std::cout << "Enter updated vegetarian preference:-" << std::endl;
            std::cin >> itemData.dietaryCategory;
            break;
        case 5:
            std::cout << "Enter updated spice level:-" << std::endl;
            std::cin >> itemData.spiceLevel;
            break;
        case 6:
            std::cout << "Enter updated food type:-" << std::endl;
            std::cin >> itemData.cuisineCategory;
            break;
        case 7:
            std::cout << "Enter updated sweet:-" << std::endl;
            std::cin >> itemData.sweet;
            break;
        case 8:
            flag = false;
            break;
        default:
            std::cout << "Invalid Choice" << std::endl;
        }
    }
    return itemData.serialize();
}

void AdminInterface::showDeleteItemPrompt()
{
    std::string itemName;
    std::cout << "Enter the name of item to delete:- " << std::endl;
    std::cin >> itemName;
    std::string userInput = std::to_string(Operation::deleteMenuItem) + "$" + itemName;
    client->sendMessage(userInput);
    std::string serverResponse = client->receiveMessage();
    if (serverResponse == "Item removed")
    {
        std::cout << "Item removed successfully" << std::endl;
    }
    else
    {
        std::cout << "Item not removed" << std::endl;
    }
}

void AdminInterface::showMenu()
{
    std::string userResponse = std::to_string(Operation::viewMenu);
    client->sendMessage(userResponse);
    std::string serverResponse = client->receiveMessage();
    std::cout << serverResponse << std::endl;
    std::vector<MenuItem> menu = helper->deserializeMenuItems(serverResponse);
    std::cout << "Item Name\tAvailability\tPrice\tMealType\tDietaryCategory\tSpiceLevel\tCuisineCategory\tSweet" << std::endl;
    for (int i = 0; i < menu.size(); i++)
    {
        std::cout << menu[i].itemName << "\t" << menu[i].availability << "\t" << menu[i].price << "\t" << menu[i].mealType << "\t" << menu[i].dietaryCategory << "\t" << menu[i].spiceLevel << "\t" << menu[i].cuisineCategory << "\t" << menu[i].sweet << std::endl;
    }
}

void AdminInterface::logout()
{
    std::string userResponse = std::to_string(Operation::logout);
    client->sendMessage(userResponse);
    std::string serverResponse = client->receiveMessage();
    return;
}
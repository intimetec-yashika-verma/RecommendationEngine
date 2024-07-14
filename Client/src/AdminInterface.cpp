#include "AdminInterface.h"
#include "Operation.h"
#include "MenuItem.h"
#include <limits>
AdminInterface::AdminInterface(Client *client) : client(client)
{
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
                     "6. Exit\n"
                     "Enter your choice :- "
                  << std::endl;
        std::string adminChoice;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin >> std::ws, adminChoice);
        std::vector<std::string> userInput = {adminChoice};

        if (adminChoice == "1")
        {
            showAddItemPrompt();
        }
        else if (adminChoice == "2")
        {
            showUpdateMenuPrompt();
        }
        else if (adminChoice == "3")
        {
            showDeleteItemPrompt();
        }
        else if (adminChoice == "4")
        {
            showMenu();
        }
        else if (adminChoice == "5")
        {
           
           logout();
        }
        else if(adminChoice == "6")
        {
           flag = false;
        }
        else
        {
             std::cout << "Invalid Choice" << std::endl;
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
    std::cout <<"What it the spice level of it ?(High/Medium/Low) "<<std::endl;
    std::getline(std::cin >> std::ws, itemData.spiceLevel);
    std::cout << "Enter the cuisine type:- " << std::endl;
    std::getline(std::cin >> std::ws, itemData.cuisineCategory);
    std::cout << "Is it a sweet dish? " << std::endl;
    std::getline(std::cin >> std::ws, itemData.sweet);
    std::string userInput = std::to_string(Operation::addMenuItem) +"$"+ itemData.serialize();
    std::cout<<"userInput "<<userInput<<std::endl;
    client->sendMessage(userInput);
    std::string serverResponse = client->receiveMessage();
}

void AdminInterface::showUpdateMenuPrompt()
{

    std::string itemToUpdate;
    std::cout << "Name the item you like to update" << std::endl;
    std::cin >> itemToUpdate;
    std::string updatedData = getDataToUpdate(itemToUpdate);
    std::string userInput = std::to_string(Operation::updateMenuItem)+ "$"+updatedData;
    client->sendMessage(userInput);
    std::string serverResponse = client->receiveMessage();
}

std::string AdminInterface::getDataToUpdate(std::string itemName)
{
   MenuItem itemData;
    bool flag = true;
    std::string userInput;
    itemData.itemName=itemName;
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
                     "Enter your choice:- ";
        std::cin >> userInput;
        if (userInput == "1")
        {
            std::cout << "Enter updated availablity:-" << std::endl;
            std::cin >> itemData.availability;
        }
        else if (userInput == "2")
        {
            std::cout << "Enter updated price:-" << std::endl;
            std::cin >> itemData.price;
        }
        else if (userInput == "3")
        {
            std::cout << "Enter updated mealType:-" << std::endl;
            std::cin >> itemData.mealType;
        }
        else if (userInput == "4")
        {
            std::cout << "Enter updated vegetarian preference:-" << std::endl;
            std::cin >> itemData.dietaryCategory;
        }
        else if(userInput == "5")
        {
            std::cout << "Enter updated spice level:-" << std::endl;
            std::cin >> itemData.spiceLevel;
        }
        else if(userInput == "6")
        {
            std::cout << "Enter updated food type:-" << std::endl;
            std::cin >> itemData.cuisineCategory;
        }
        else if(userInput == "7")
        {
            std::cout << "Enter updated sweet:-" << std::endl;
            std::cin >> itemData.sweet;
        }
        else
        {
            flag = false;
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
}

void AdminInterface::showMenu()
{
    std::string userResponse = std::to_string(Operation::viewMenu);
    client->sendMessage(userResponse);
    std::string serverResponse = client->receiveMessage();
    
}

void AdminInterface::logout()
{
    std::string userResponse = std::to_string(Operation::logout);
    client->sendMessage(userResponse);
    std::string serverResponse = client->receiveMessage();
    return;
}
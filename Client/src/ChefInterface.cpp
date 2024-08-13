#include <limits>
#include <algorithm>
#include "ChefInterface.h"
#include "Operation.h"
#include "VoteCount.h"
#include "ItemReview.h"
ChefInterface::ChefInterface(Client *client) : client(client)
{
    helper = new Helper();
}
void ChefInterface::showUserMenuPrompt()
{
    std::cout << "Welcome Chef\n\n"
              << std::endl;

    bool flag = true;
    while (flag)
    {
        std::cout << "Select the operation which you like to perform\n"
                     "1. Get Recommendation\n"
                     "2. RollOut menu for tommorow\n"
                     "3. Discard menu\n"
                     "4. logout\n"
                     "Enter your choice :- "
                  << std::endl;
        std::string chefChoice;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin >> std::ws, chefChoice);
        std::vector<std::string> userInput = {chefChoice};

        if (chefChoice == "1")
        {

            showRecommendationMenu();
        }
        else if (chefChoice == "2")
        {
            getVoteCountForMealType();
        }
        else if (chefChoice == "3")
        {
            discardItemFromMenu();
        }
        else if (chefChoice == "4")
        {
            logout();
            flag = false;
        }
    }
}

void ChefInterface::getRecommendationMenu(std::string mealType)
{
    std::string userResponse = std::to_string(Operation::getRecommandationFromEngine) + "$" + mealType;
    client->sendMessage(userResponse);
    std::string menu = client->receiveMessage();
    std::cout << "Select items for tomorrow's " << mealType << ":-" << std::endl;
    std::vector<ItemReview> items = helper->deserializeItemReview(menu);
    for (int i = 0; i < items.size(); i++)
    {
        std::cout << i + 1 << ". " << items[i].itemName << "  " << items[i].averageRating << " ";
        for (int j = 0; j < items[i].sentiments.size(); j++)
        {
            std::cout << items[i].sentiments[j] << ",";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::string selectedItems = std::to_string(Operation::selectMenuForNextDay) + "$" + mealType + ",";
    while (true)
    {
        std::string itemName;
        std::cout << "Enter the item name or 0 to stop:-" << std::endl;
        std::getline(std::cin >> std::ws, itemName);
        if (itemName == "0")
        {
            break;
        }
        if (std::find_if(items.begin(), items.end(), [itemName](ItemReview item)
                         { return item.itemName == itemName; }) == items.end())
        {
            std::cout << "Invalid Item" << std::endl;
            continue;
        }
        selectedItems += itemName + ",";
    }
    selectedItems = selectedItems.substr(0, selectedItems.size() - 1);
    client->sendMessage(selectedItems);
    std::string response = client->receiveMessage();
    std::cout << response << std::endl;
}

void ChefInterface::showRecommendationMenu()
{
    bool flag = true;
    while (flag)
    {
        std::cout << "Choose the meal type:-\n"
                     "1. Breakfast\n"
                     "2. Lunch\n"
                     "3. Dinner\n"
                     "4. Back\n";
        int userInput;
        std::cin >> userInput;
        switch (userInput)
        {
        case 1:
            getRecommendationMenu("Breakfast");
            break;
        case 2:
            getRecommendationMenu("Lunch");
            break;
        case 3:
            getRecommendationMenu("Dinner");
            break;
        case 4:
            flag = false;
            break;
        default:
            std::cout << "Invalid Choice" << std::endl;
        }
    }
}

void ChefInterface::publishTodayMenu(std::string mealType)
{
    std::string userResponse = std::to_string(Operation::getVoteCountList) + "$" + mealType;
    client->sendMessage(userResponse);
    std::string serverResponse = client->receiveMessage();
    std::vector<VoteCount> voteCountList = helper->deserializeVoteCountList(serverResponse);
    std::cout << "Select Items to cook tomorrow" << std::endl;
    for (int i = 0; i < voteCountList.size(); i++)
    {
        std::cout << i + 1 << ". " << voteCountList[i].itemName << " " << voteCountList[i].count << std::endl;
    }
    std::string selectedItems = std::to_string(Operation::PublishMenuForToday) + "$" + mealType + ",";
    while (true)
    {
        std::cout << "Enter the item name to cook tomorrow or 0 to stop" << std::endl;
        std::string itemName;
        std::getline(std::cin >> std::ws, itemName);
        if (itemName == "0")
        {
            break;
        }
        if (std::find_if(voteCountList.begin(), voteCountList.end(), [itemName](VoteCount item)
                         { return item.itemName == itemName; }) == voteCountList.end())
        {
            std::cout << "Invalid Item" << std::endl;
            continue;
        }
        selectedItems += itemName + ",";
    }
    selectedItems = selectedItems.substr(0, selectedItems.size() - 1);
    client->sendMessage(selectedItems);
    std::string response = client->receiveMessage();
    std::cout << response << std::endl;
}

void ChefInterface::getVoteCountForMealType()
{
    bool flag = true;
    while (flag)
    {
        std::cout << "Choose the meal type:-\n"
                     "1. Breakfast\n"
                     "2. Lunch\n"
                     "3. Dinner\n"
                     "4. Back\n";
        int userInput;
        std::cin >> userInput;
        switch (userInput)
        {
        case 1:
            publishTodayMenu("Breakfast");
            break;
        case 2:
            publishTodayMenu("Lunch");
            break;
        case 3:
            publishTodayMenu("Dinner");
            break;
        case 4:
            flag = false;
            break;
        default:
            std::cout << "Invalid Choice" << std::endl;
        }
    }
}

void ChefInterface::discardItemFromMenu()
{
    std::string userResponse = std::to_string(Operation::discardMenuItem);
    client->sendMessage(userResponse);
    std::string menuItemList = client->receiveMessage();
    std::cout << menuItemList << std::endl;
    std::vector<ItemReview> items = helper->deserializeItemReview(menuItemList);
    for (int i = 0; i < items.size(); i++)
    {
        std::cout << i + 1 << ". " << items[i].itemName << " " << items[i].averageRating << " ";
        for (int j = 0; j < size(items[i].sentiments); j++)
        {
            std::cout << items[i].sentiments[j] << ",";
        }

        std::cout << "\n1. Discard Item\n"
                     "2. Ask Home recipe from employees\n";
        int userInput;
        std::cin >> userInput;
        switch (userInput)
        {
        case 1:
        {
            std::string userChoice = std::to_string(Operation::deleteMenuItem) + "$" + items[0].itemName;
            client->sendMessage(userChoice);
            break;
        }
        case 2:
        {
            std::string userChoice = std::to_string(Operation::getHomeReceipe) + "$" + items[0].itemName;
            client->sendMessage(userChoice);
            break;
        }
        default:
            std::cout << "Invalid Choice" << std::endl;
        }
        std::string response = client->receiveMessage();
    }
}

void ChefInterface::logout()
{
    std::string userResponse = std::to_string(Operation::logout);
    client->sendMessage(userResponse);
    std::string serverResponse = client->receiveMessage();
}
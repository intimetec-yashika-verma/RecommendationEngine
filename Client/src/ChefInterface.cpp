#include <limits>
#include "ChefInterface.h"
#include "Operation.h"
#include "RequestSerializer.h"
#include "ItemReview.h"
ChefInterface::ChefInterface(Client *client) : client(client)
{
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
    std::vector<ItemReview> items = RequestSerializer::deserializeItemReview(menu);
    for (int i = 0; i < items.size(); i++)
    {
        std::cout << i + 1 << ". " << items[i].itemName << "  " << items[i].averageRating << " ";
        for (auto i : items[i].sentiments)
        {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }
    std::string selectedItems = std::to_string(Operation::selectMenuForNextDay) + "$" + mealType + ",";
    while (true)
    {
        std::string itemName;
        std::cout << "Enter the item name   our 0 to stop:-" << std::endl;
        std::cin >> itemName;
        if (itemName == "0")
        {
            break;
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
            getRecommendationMenu("breakfast");
            break;
        case 2:
            getRecommendationMenu("lunch");
            break;
        case 3:
            getRecommendationMenu("dinner");
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
    std::vector<VoteCount> voteCountList = RequestSerializer::deserializeVoteCountList(serverResponse);
    std::cout << "Select Items to cook tomorrow" << std::endl;
    for (int i = 0; i < voteCountList.size(); i++)
    {
        std::cout << i + 1 << ". " << voteCountList[i].itemName << " " << voteCountList[i].count << std::endl;
    }
    std::string selectedItems = std::to_string(Operation::PublishMenuForToday) + "," + mealType + ",";
    while (true)
    {
        std::cout << "Enter the item name to cook tomorrow or 0 to stop" << std::endl;
        std::string itemName;
        std::cin >> itemName;
        if (itemName == "0")
        {
            break;
        }
        selectedItems += itemName + ",";
    }
    selectedItems = selectedItems.substr(0, selectedItems.size() - 1);
    client->sendMessage(selectedItems);
    std::string response = client->receiveMessage();
    std::cout << response<< std::endl;
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
            publishTodayMenu("breakfast");
            break;
        case 2:
            publishTodayMenu("lunch");
            break;
        case 3:
            publishTodayMenu("dinner");
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
    std::vector<ItemReview> items = RequestSerializer::deserializeItemReview(menuItemList);
    std::cout<<"1. Discard Item\n"
             "2. Ask Home recipe from employees\n";
    std::string userInput;
    std::cin>>userInput;
    if(userInput == "1")
    {
        std::string userChoice = std::to_string(Operation::deleteMenuItem)+"$"+items[0].itemName;
        client->sendMessage(userChoice);
    }
    else if(userInput == "2")
    {
        std::string userChoice = std::to_string(Operation::getHomeReceipe)+"$"+items[0].itemName;
        client->sendMessage(userChoice);
    }
    std::string response = client->receiveMessage();
}

void ChefInterface::logout()
{
    std::string userResponse = std::to_string(Operation::logout);
    client->sendMessage(userResponse);
    std::string serverResponse = client->receiveMessage();
}
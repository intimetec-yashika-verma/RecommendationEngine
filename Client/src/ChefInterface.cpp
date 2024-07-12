#include <limits>
#include "ChefInterface.h"
#include "Operation.h"
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
                     "2. Get list of voted Items\n"
                     "3. Update next day menu\n"
                     "4. Discard menu\n"
                     "5. Exit\n"
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
            publishTodayMenu();
        }
        else if (chefChoice == "3")
        {
            showMenu();
        }
        else if (chefChoice == "4")
        {
            discardMenuItem();
        }
        else if (chefChoice == "5")
        {
            client->sendMessage(userInput);
            flag = false;
        }
    }
}

void ChefInterface::getRecommendationMenu(std::string mealType)
{
    std::string userResponse = std::to_string(Operation::getRecommandationFromEngine)+"$"+mealType;
    client->sendMessage(userResponse);
    std::string menu = client->receiveMessage();
    std::cout << std::endl;
    std::cout << "Select items for tomorrow's " << mealType << ":-" << std::endl;
    std::vector<std::string> selectedItems = {"7"};
    for (int i = 0; i <= 2; i++)
    {
        std::string name;
        std::getline(std::cin >> std::ws, name);
        selectedItems.push_back(name);
    }
    client->sendMessage(selectedItems);
    std::vector<std::string> response = client->receiveMessage();
    std::cout << response[0] << std::endl;
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
        switch(userInput)
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
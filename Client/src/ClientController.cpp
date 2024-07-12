#include "ClientController.h"
#include "Client.h"
#include "Operation.h"
#include "Feedback.h"
#include <vector>
#include <iostream>
#include <string>
#include <limits>
#include <unordered_map>
#include "Serializer.h"
#include "MenuItem.h"
#include "IUserInterface.h"
#include "AdminInterface.h"
#include "ChefInterface.h"
#include "EmployeeInterface.h"
#include "LoginCredential.h"

ClientController::ClientController(Client *client)
{
    this->client = client;
}
Role ClientController::loginPrompt()
{
    LoginCredential loginCredentials;
    std::cout << "enter email id: " << std::endl;
    std::cin >> loginCredentials.emailId;
    std::cout << "enter password: " << std::endl;
    std::cin >> loginCredentials.password;
    std::string userInput = std::to_string(Operation::login) + 
    client->sendMessage(userInput);
    std::string clientRole = client->receiveMessage();
    return Role(std::stoi(clientRole));
}


void ClientController::publishTodayMenu()
{
    std::vector<std::string> userResponse = {"8", "list"};
    client->sendMessage(userResponse);
    std::vector<std::string> votedItems = client->receiveMessage();
    for (int i = 0; i < votedItems.size(); i++)
    {
        if (i % 2 != 0)
        {
            std::cout << i << " " << votedItems[i];
        }
        else
        {
            std::cout << votedItems[i] << std::endl;
        }
    }
    std::cout << "Select Items to cook tomorrow" << std::endl;
    std::vector<std::string> todaysMenu = {"9"};
    for (int i = 0; i < 2; i++)
    {
        std::string userInput;
        std::cin >> userInput;
        todaysMenu.push_back(userInput);
    }
    client->sendMessage(todaysMenu);
    std::vector<std::string> response = client->receiveMessage();
    std::cout << response[0] << std::endl;
}

void ClientController::showEmployeeMenu()
{
    std::cout << "Welcome Employee\n\n"
              << std::endl;

    bool flag = true;
    while (flag)
    {
        std::cout << "Select the operation which you like to perform\n"
                     "1. View Notifications\n"
                     "2. Vote For Tommorrow's Menu\n"
                     "3. Give Feeback\n"
                     "4. Share review On Discarded item\n"
                     "Enter your choice :- "
                  << std::endl;
        std::string employeeChoice;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin >> std::ws, employeeChoice);

        if (employeeChoice == "1")
        {
            viewNotification();
        }
        else if (employeeChoice == "2")
        {
            voteForTomorrowMenu();
        }
        else if (employeeChoice == "3")
        {
            giveFeedback();
        }
        else if(employeeChoice == "4")
        {
           giveReviewOnDiscardedItem();
        }
    }
}

void ClientController::viewNotification()
{
    std::vector<std::string> userResponse = {"10", "notification"};
    client->sendMessage(userResponse);
    std::vector<std::string> notificationData = client->receiveMessage();
    for (int i = 0; i < notificationData.size(); i++)
    {
        std::cout << notificationData[i] << std::endl;
    }
}

void ClientController::voteForTomorrowMenu()
{
    std::vector<std::string> userResponse = {"12", "sendItemList"};
    client->sendMessage(userResponse);
    std::vector<std::string> menuItemList = client->receiveMessage();
    std::cout << "Select item for tomorrow's Menu:-" << std::endl;
    for (int i = 0; i < menuItemList.size(); i++)
    {
        std::cout << menuItemList[i] << std::endl;
    }
    std::vector<std::string> votedItems{"13"};
    std::string breakfastItem, lunchItem, dinnerItem;
    std::getline(std::cin >> std::ws, breakfastItem);
    std::getline(std::cin >> std::ws, lunchItem);
    std::getline(std::cin >> std::ws, dinnerItem);
    votedItems.push_back(breakfastItem);
    votedItems.push_back(lunchItem);
    votedItems.push_back(dinnerItem);
    client->sendMessage(votedItems);
    menuItemList = client->receiveMessage();
}
void ClientController::giveFeedback()
{
    std::vector<std::string> userResponse = {"11","feedback"};
    client->sendMessage(userResponse);
    std::vector<std::string> menuItemList = client->receiveMessage();
    std::unordered_map<std::string,Feedback> feedbacks;
    for(int i= 0;i<menuItemList.size();i++)
    {
        Feedback feedbackData;
        std::cout<<"Enter rating Data:- "<<std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin>>feedbackData.rating;
        std::cout<<"Enter the comment for dish:- "<<std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin >> std::ws, feedbackData.comment);
        feedbacks[menuItemList[i]]=feedbackData;
    }
    std::string input = "14,"+Serializer::serializeFeedbacks(feedbacks);
    std::cout<<input<<std::endl;
    client->sendMessage(input);
    menuItemList = client->receiveMessage();
}

void ClientController::discardMenuItem()
{
    std::vector<std::string> userResponse = {"15","discardList"};
    client->sendMessage(userResponse);
    std::vector<std::string> menuItemList = client->receiveMessage();
    for(int i=0;i<menuItemList.size();i++)
    {
        std::cout<<menuItemList[i]<<std::endl;
    }
    std::cout<<"1. Discard Item\n"
             "2. Ask Home recipe from employees\n";
    std::string userInput;
    std::cin>>userInput;
    if(userInput == "1")
    {
        std::vector<std::string> userChoice = {"3",menuItemList[0]};
        client->sendMessage(userChoice);
    }
    else if(userInput == "2")
    {
        std::vector<std::string> userChoice = {"16",menuItemList[0]};
        client->sendMessage(userChoice);
    }
    std::vector<std::string> response = client->receiveMessage();
}

void ClientController::giveReviewOnDiscardedItem()
{
   std::vector<std::string> userResponse = {"17","review"};
    client->sendMessage(userResponse);
    std::vector<std::string> menuItemList = client->receiveMessage();
    std::unordered_map<std::string,std::vector<std::string>> feedbacks;
    feedbacks[menuItemList[0]]={"18"};
    std::string userInput;
    std::cout<<"What didn't you like about "<<menuItemList[0]<<std::endl;
    std::getline(std::cin >> std::ws, userInput);
    feedbacks[menuItemList[0]].push_back(userInput);
    std::cout<<"How would you like "<<menuItemList[0]<<" to taste?"<<std::endl;
    std::getline(std::cin >> std::ws, userInput);
    feedbacks[menuItemList[0]].push_back(userInput);
    std::cout<<"Share your mom’s recipe"<<std::endl;
    std::getline(std::cin >> std::ws, userInput);
    feedbacks[menuItemList[0]].push_back(userInput);
    client->sendMessage(menuItemList[0]);
}
void ClientController::run()
{
   Role role = loginPrompt();
   switch(role)
   {
       case Role::admin:
       {
           userInterface = new AdminInterface(client);
           break;
       }
       case Role::chef:
       {
          userInterface = new ChefInterface(client);
           break;
       }
       case Role::employee:
       {
          userInterface = new EmployeeInterface(client);
           break;
       }
   }
   userInterface->showUserMenuPrompt();
   
}


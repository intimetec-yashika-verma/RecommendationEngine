#include <limits>
#include <unordered_map>
#include "EmployeeInterface.h"
#include "Operation.h"
#include "StringSerializer.h"
#include "ItemReview.h"
#include "RequestSerializer.h"
#include "Feedback.h"
#include "Serializer.h"
#include "DiscardedItemReview.h"


EmployeeInterface::EmployeeInterface(Client *client) : client(client)
{
}

void EmployeeInterface::showUserMenuPrompt()
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
            getListOfItemsToVote();
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

void EmployeeInterface::viewNotification()
{
    std::string userResponse = std::to_string(Operation::viewNotification);
    client->sendMessage(userResponse);
    std::string notificationData = client->receiveMessage();
    std::vector<std::string> notificationVector = StringSerializer::deserialize(notificationData);
    for (int i = 0; i < notificationData.size(); i++)
    {
        std::cout << notificationData[i] << std::endl;
    }
}

void EmployeeInterface::voteForTomorrowMenu(std::string mealType)
{
    std::string userResponse = std::to_string(Operation::voteItemFromTomorrowMenu)+"$"+mealType;
    client->sendMessage(userResponse);
    std::string menuItemList = client->receiveMessage();
    std::cout << "Select item for tomorrow's Menu:-" << std::endl;
    std::vector<ItemReview> items = RequestSerializer::deserializeItemReview(menuItemList);
    for(int i=0;i<items.size();i++)
    {
        std::cout<<i+1<<". "<<items[i].itemName<<"  "<<items[i].averageRating<<" ";
        for(auto i:items[i].sentiments)
        {
            std::cout<<i<<" ";
        }
        std::cout<<std::endl;
    }
    std::string ItemstoVote = std::to_string(Operation::saveVotingResponse);
    std::vector<std::string> votedItems;
    while(true)
    {
        std::string itemName;
        std::cout<<"Enter the item name or 0 to stop:-"<<std::endl;
        std::cin>>itemName;
        if(itemName == "0")
        {
            break;
        }
        votedItems.push_back(itemName);
    }
    std::string votedItemsString = ItemstoVote+"$"+ StringSerializer::serialize(votedItems);
    client->sendMessage(votedItemsString);
    std::string serverResponse = client->receiveMessage();
}

void EmployeeInterface::getListOfItemsToVote()
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
            voteForTomorrowMenu("breakfast");
            break;
        case 2:
            voteForTomorrowMenu("lunch");
            break;
        case 3:
            voteForTomorrowMenu("dinner");
            break;
        case 4:
            flag = false;
            break;
        default:
            std::cout << "Invalid Choice" << std::endl;
        }
    }
}

void EmployeeInterface::giveFeedback()
{
    std::string userResponse = std::to_string(Operation::provideFeedback);
    client->sendMessage(userResponse);
    std::string menuItemList = client->receiveMessage();
    std::vector<std::string> menuItemListVector = StringSerializer::deserialize(menuItemList);
    std::unordered_map<std::string,Feedback> feedbacks;
    for(int i= 0;i<menuItemListVector.size();i++)
    {
        std::cout<<"Enter feedback for dish:- "<<menuItemListVector[i]<<std::endl;
        Feedback feedbackData;
        std::cout<<"Enter rating Data:- "<<std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin>>feedbackData.rating;
        std::cout<<"Enter the comment for dish:- "<<std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin >> std::ws, feedbackData.comment);
        feedbacks[menuItemListVector[i]]=feedbackData;
    }
    std::string input = std::to_string(Operation::saveFeedback)+"$"+Serializer::serializeFeedbacks(feedbacks);
    std::cout<<input<<std::endl;
    client->sendMessage(input);
    std::string serverResponse = client->receiveMessage();
}

void EmployeeInterface::giveReviewOnDiscardedItem()
{
    std::string userResponse = std::to_string(Operation::getDiscardedMenuItemsList);
    client->sendMessage(userResponse);
    std::string discardedItemData = client->receiveMessage();
    std::vector<ItemReview> discardedItemVector = RequestSerializer::deserializeItemReview(discardedItemData);
        DiscardedItemReview discardedItemReview;
    for(int i= 0;i<discardedItemVector.size();i++)
    {
        std::cout<<i+1<<". "<<discardedItemVector[i].itemName<<"  "<<discardedItemVector[i].averageRating<<" ";
        for(auto i:discardedItemVector[i].sentiments)
        {
            std::cout<<i<<" ";
        }
        std::cout<<std::endl;
        discardedItemReview.itemName = discardedItemVector[i].itemName;
        std::cout<<"What do you think about this item?"<<std::endl;
        std::getline(std::cin >> std::ws, discardedItemReview.negativePointOnItem);
        std::cout<<"How would you like to taste it?"<<std::endl;
        std::getline(std::cin >> std::ws, discardedItemReview.improvementPointOnItem);
        std::cout<<"Share home recepie?"<<std::endl;
        std::getline(std::cin >> std::ws, discardedItemReview.homeRecepie);
    }
    std::string input = std::to_string(Operation::getFeedbackOnDiscardedItem)+"$"+discardedItemReview.serialize();
    std::cout<<input<<std::endl;
    client->sendMessage(input);
    std::string serverResponse = client->receiveMessage();
}
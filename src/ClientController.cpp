#include "../inc/ClientController.h"
#include "../inc/Client.h"
#include <vector>
#include <iostream>
#include <string>
#include <limits>

ClientController::ClientController(Client *client)
{
    this->client = client;
}
void ClientController::LoginPrompt()
{
    std::vector<std::string> loginCredentials;
    std::string response;
    std::cout << "enter email id: " << std::endl;
    std::cin >> response;
    loginCredentials.push_back(response);
    std::cout << "enter password: " << std::endl;
    std::cin >> response;
    loginCredentials.push_back(response);
    client->sendMessage(loginCredentials);
}

void ClientController::showMenuPrompt(std::string userRole)
{
    if (userRole == "1")
    {
        showAdminMenu();
    }
}
int ClientController::showAdminMenu()
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
                     "5. Exit\n"
                     "Enter your choice :- "<<std::endl;
    std::string adminChoice;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin>>std::ws, adminChoice);
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
        client->sendMessage(userInput);
        flag = false;
    }
    else
    {
        std::cout << "Invalid Choice" << std::endl;
    }
    }
    return 0;
}
void ClientController::showAddItemPrompt()
{
    std::vector<std::string> userResponse;
    userResponse.push_back("1");
    std::string userInput;
    std::cout << "Enter Item name:- " << std::endl;
    std::cin >> userInput;
    userResponse.push_back(userInput);
    std::cout << "Enter Item price:- " << std::endl;
    std::cin >> userInput;
    userResponse.push_back(userInput);
    std::cout << "Enter Item availablity:- " << std::endl;
    std::cin >> userInput;
    userResponse.push_back(userInput);
    std::cout << "Enter meal type(breakfast/lunch/dinner):- " << std::endl;
    std::cin >> userInput;
    userResponse.push_back(userInput);
    client->sendMessage(userResponse);
}

void ClientController::showUpdateMenuPrompt()
{
    std::vector<std::string> userResponse(6, "");
    userResponse[0] = "2";
    std::string userInput;
    std::cout << "Name the item you like to update" << std::endl;
    std::cin>>userInput;
    userResponse[1] = userInput;

    std::vector<std::string> updatedData=  getDataToUpdate();
    userResponse.insert(userResponse.end(),updatedData.begin(),updatedData.end());
    for(int i=0;i<6;i++)
    {
        std::cout<<userResponse[i]<<",";
    }
    std::cout << std::endl;
    client->sendMessage(userResponse);
}

std::vector<std::string> ClientController::getDataToUpdate()
{
    std::vector<std::string> userResponse(4,"");
    bool flag = true;
    std::string userInput;
    while (flag)
    {
        std::cout << "Select value which you want to update\n"
                     "1. Name\n"
                     "2. Availablity\n"
                     "3. Price\n"
                     "4. MealType\n"
                     "5. Done\n"
                     "Enter your choice:- ";
        std::cin >> userInput;
        if (userInput == "1")
        {
            std::cout << "Enter updated Name:-" << std::endl;
            std::cin >> userInput;
            userResponse[0]=userInput;
        }
        else if (userInput == "2")
        {
            std::cout << "Enter updated availablity:-" << std::endl;
            std::cin >> userInput;
            userResponse[1]=userInput;
        }
        else if (userInput == "3")
        {
            std::cout << "Enter updated price:-" << std::endl;
            std::cin >> userInput;
            userResponse[2]=userInput;
        }
        else if (userInput == "4")
        {
            std::cout << "Enter updated mealType:-" << std::endl;
            std::cin >> userInput;
            userResponse[3]=userInput;
        }
        else
        {
            flag=false;
        }
    }
    return userResponse;
}

void ClientController::showDeleteItemPrompt()
{
    std::string userChoice;
    std::vector <std::string> userResponse;
    userResponse.push_back("3");
    std::cout<<"Enter the name of item to delete:- "<<std::endl;
    std::cin>>userChoice;
    userResponse.push_back(userChoice);
    client->sendMessage(userResponse);

}
void ClientController::showMenu()
{
   std::vector<std::string> userResponse{"4"};
   client->sendMessage(userResponse);
   std::vector<std::string>menu=client->receiveMessage();
   int itemCount=4;
   int counter=0;
   for(int i=0;i<menu.size()/itemCount;i++)
   {
    std::cout<<menu[1]<<std::endl;
    for(int j=0;j<itemCount;j++)
    {
        std::cout<<menu[counter]<<" ";
        counter++;
    }
    std::cout<<std::endl;
   }
}
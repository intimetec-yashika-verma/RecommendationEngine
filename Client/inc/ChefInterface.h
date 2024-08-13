
#include "IUserInterface.h"
#include "Client.h"
#include "Helper.h"
class ChefInterface : public IUserInterface
{
public:
    ChefInterface(Client *client);
    void showUserMenuPrompt();
    void getRecommendationMenu(std::string mealType);
    void showRecommendationMenu();
    void publishTodayMenu(std::string mealType);
    void getVoteCountForMealType();
    void discardItemFromMenu();
    void logout();

private:
    Helper *helper;
    Client *client;
};
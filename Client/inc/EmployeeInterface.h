#include "IUserInterface.h"
#include "Client.h"
class EmployeeInterface : public IUserInterface
{
public:
    EmployeeInterface(Client *client);
    void showUserMenuPrompt();
    void viewNotification();
    void voteForTomorrowMenu(std::string mealType);
    void getListOfItemsToVote();
    void giveFeedback();
    void giveReviewOnDiscardedItem();

private:
    Client *client;
};
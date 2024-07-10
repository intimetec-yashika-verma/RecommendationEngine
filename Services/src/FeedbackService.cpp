#include "FeedbackService.h"
#include "FeedbackDAO.h"
#include "MenuDAO.h"
#include <sstream>
#include <iomanip>

FeedbackService::FeedbackService(FeedbackDAO *feedbackDAO) : feedbackDAO(feedbackDAO)
{
}
Feedback *FeedbackService::getItemFeedback(const std::string &ItemId)
{
    // std::cout<<"getItemFeedback"<<std::endl;
    // std::cout<<"getItemFeedback2"<<std::endl;
    // Feedback *obj = feedbackDAO->getItemFeedback(ItemId);
    // return obj;
} 

void FeedbackService::addItemFeedback(std::vector<std::string> itemList)
{

    int counter = 1;
    for (int i = 0; i < itemList.size() / 3; i++)
    {
        std::string lastId = feedbackDAO->getLastUserId();
        std::cout << "lastId" << lastId << std::endl;
        int num = std::stoi(lastId.substr(2)) + 1;

        std::ostringstream oss;
        oss << "FB" << std::setw(3) << std::setfill('0') << num;
        std::string newId = oss.str();
        std::cout << "newId" << newId << std::endl;
        MenuDAO *dao = new MenuDAO();
        std::string id = dao->getIdFromName(itemList[counter]);
        std::cout<<id<<" "<<itemList[counter + 1]<<" "<<itemList[counter + 2]<<std::endl;
        feedbackDAO->addItemFeedback(newId, id, itemList[counter + 2], itemList[counter + 1]);
        counter = counter + 3;
    }
}


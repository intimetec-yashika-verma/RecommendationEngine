#include "FeedbackService.h"
#include "FeedbackDAO.h"

Feedback* FeedbackService::getItemFeedback(const std::string &ItemId)
{
   // std::cout<<"getItemFeedback"<<std::endl;
    FeedbackDAO dao=FeedbackDAO();
   // std::cout<<"getItemFeedback2"<<std::endl;
    Feedback* obj=dao.getItemFeedback(ItemId);
    return obj;

}
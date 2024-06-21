#include<vector>
#include<iostream>
#include <unordered_map>
#include "../inc/Feedback.h"
#pragma once
class FeedbackService
{
   public: 
    std::unordered_map<std::string, Feedback> itemFeedbacks;
    
    Feedback* getItemFeedback(const std::string &ItemId);

};
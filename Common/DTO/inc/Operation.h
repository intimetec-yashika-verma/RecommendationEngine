#pragma once
enum Operation : int
{
   login = 1,
   addMenuItem = 2,
   deleteMenuItem = 3,
   updateMenuItem = 4,
   viewMenu = 5,
   getRecommandationFromEngine = 6,
   selectMenuForNextDay = 7,
   getVoteCountList = 8,
   PublishMenuForToday = 9,
   viewNotification = 10,
   provideFeedback = 11,
   voteItemFromTomorrowMenu = 12,
   saveVotingResponse = 13,
   saveFeedback = 14,
   discardMenuItem = 15,
   getFeedbackOnDiscardedItem = 16,
   getDiscardedMenuItemsList = 17,
   getHomeReceipe = 18,
   logout = 18
};
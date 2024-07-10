#pragma once
enum Operation : int
{
   login = 1,
   AddMenuItem = 2,
   DeleteMenuItem = 3,
   UpdateMenuItem = 4,
   ViewMenu = 5,
   GetRecommandationFromEngine = 6,
   SelectMenuForNextDay = 7,
   GetVoteCountList = 8,
   PublishMenuForToday = 9,
   ViewNotification = 10,
   ProvideFeedback = 11,
   VoteItemFromTomorrowMenu = 12,
   SaveVotingResponse = 13,
   saveFeedback=14,
   discardMenuItem = 15,
   getHomeReceipe = 16,
   getDiscardedMenuItemsList = 17
};
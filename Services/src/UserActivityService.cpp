#include "UserActivityService.h"

UserActivityService::UserActivityService(UserActivityDAO *userActivityDAO) : userActivityDAO(userActivityDAO)
{
}

void UserActivityService::saveUserActivity(std::string userId, std::string activity)
{
    userActivityDAO->saveUserActivity(userId, activity);
}
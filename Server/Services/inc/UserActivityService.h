#pragma once
#include "UserActivityDAO.h"
class UserActivityService
{
public:
    UserActivityService(UserActivityDAO *userActivityDAO);
    void saveUserActivity(std::string userId, std::string activity);

private:
    UserActivityDAO *userActivityDAO;
};
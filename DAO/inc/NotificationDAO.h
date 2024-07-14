#pragma once
#include <iostream>
#include <vector>
#include "DatabaseConnection.h"

class NotificationDAO
{
public:
NotificationDAO();
    void addNewNotification(std::string notificationMessage);
    std::string getLastUserId();
    std::vector<std::string> getUserNotifcations(std::string userId);

private:
    DatabaseConnection *dbConnection;
    MYSQL *connection;
};
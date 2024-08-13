#pragma once
#include <iostream>
#include <vector>
#include "DatabaseConnection.h"

class NotificationDAO
{
public:
    NotificationDAO();
    void addNewNotification(std::string notificationMessage);
    std::vector<std::string> getUserNotifcations(std::string userId);
    void setSeenStatus(std::string userId);

private:
    DatabaseConnection *dbConnection;
    MYSQL *connection;
};
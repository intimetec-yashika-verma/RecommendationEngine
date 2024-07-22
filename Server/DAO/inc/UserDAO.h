#pragma once
#include "DatabaseConnection.h"
#include "UserProfile.h"
class UserDAO
{
public:
    UserDAO();
    UserProfile getUserData(std::string email, std::string userName);

private:
    DatabaseConnection *dbConnection;
    MYSQL *connection;
};
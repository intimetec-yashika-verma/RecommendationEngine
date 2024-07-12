#include <iostream>
#include "DatabaseConnection.h"
class UserActivityDAO{
    public:
    void saveUserActivity(std::string userId, std::string activity) ;    
    private:
    DatabaseConnection *dbConnection;
    MYSQL *connection;
};
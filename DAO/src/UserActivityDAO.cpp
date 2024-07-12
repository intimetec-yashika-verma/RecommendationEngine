#include "UserActivityDAO.h"
#include "DatabaseConnection.h"

UserActivityDAO::UserActivityDAO(): dbConnection{DatabaseConnection::getInstance()}
{
    connection=dbConnection->getConnection();
}

void UserActivityDAO::saveUserActivity(std::string userId, std::string activity) {
    std::string query = "INSERT INTO UserActivity (user_id, activity) VALUES ('" + userId + "', '" + activity + "')";
    if (mysql_query(connection, query.c_str())) {
        std::cout << "Error in saving user activity: " << mysql_error(connection) << std::endl;
    }
}
#include "UserDAO.h"
#include "DatabaseConnection.h"
#include "User.h"
#include "UserProfile.h"
UserDAO::UserDAO() : dbConnection{DatabaseConnection::getInstance()}
{
    connection = dbConnection->getConnection();
}
UserProfile UserDAO::getUserData(std::string email, std::string password)
{
    std::string query = "SELECT * FROM users WHERE email = '" + email + "' AND password = '" + password + "'";
    if (mysql_query(connection, query.c_str()))
    {
        std::cerr << "Query failed: " << mysql_error(connection) << std::endl;
    }

    MYSQL_RES *result = mysql_store_result(connection);
    if (result == nullptr)
    {
        std::cerr << "Store result failed: " << mysql_error(connection) << std::endl;

    }
    UserProfile userProfile;
    MYSQL_ROW   row = mysql_fetch_row(result);
    userProfile.userId = row[0];
    userProfile.role = row[3];
    userProfile.dietaryCategory = row[4];
    userProfile.spiceLevel = row[5];
    userProfile.PreferanceType = row[6];
    userProfile.SweetTooth = row[7];
    mysql_free_result(result);

    return userProfile;
}
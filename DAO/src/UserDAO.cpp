#include "UserDAO.h"
#include "DatabaseConnection.h"
#include "User.h"
UserDAO::UserDAO() : dbConnection{DatabaseConnection::getInstance()}
{
    connection = dbConnection->getConnection();
}
User UserDAO::getUserData(std::string email, std::string password)
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

    MYSQL_ROW   row = mysql_fetch_row(result);
    std::string id=row[0];
    std::string mail = row[1];
    std::string userPassword = row[2];
    int role = std::stoi(row[3]);
    std::cout<<id+mail+userPassword+" ";
    std::cout<<role<<std::endl;
    mysql_free_result(result);
    User userData =User(id,mail,userPassword,role);
    return userData;
}
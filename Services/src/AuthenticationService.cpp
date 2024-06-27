#include "AuthenticationService.h"
#include "DatabaseConnection.h"
#include <iostream>
#include <vector>

AuthenticationService::AuthenticationService() {
}

AuthenticationService::~AuthenticationService() {
   
}

bool AuthenticationService::authenticateUser(std::vector<std::string> userCredentials) {
    DatabaseConnection* dbConnection = DatabaseConnection::getInstance();
    MYSQL* connection = dbConnection->getConnection();

    std::string query = "SELECT * FROM users WHERE email = '" + email + "' AND password = '" + password + "'";
    if (mysql_query(connection, query.c_str())) {
        std::cerr << "Query failed: " << mysql_error(connection) << std::endl;
        return false;
    }

    MYSQL_RES* result = mysql_store_result(connection);
    if (result == nullptr) {
        std::cerr << "Store result failed: " << mysql_error(connection) << std::endl;
        return false;
    }

    bool authenticated = mysql_num_rows(result) > 0;
    mysql_free_result(result);
    return authenticated;
}

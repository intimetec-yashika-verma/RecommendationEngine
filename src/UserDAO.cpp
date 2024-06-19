#include "../inc/AdminDAO.h"

void AdminDao::initConnection() {
    connection = DatabaseConnection::getInstance().getConnection();
}

bool AdminDao::isAdminValid(const std::string& username, const std::string& password) {
    initConnection();

    std::string query = "SELECT * FROM admins WHERE username = '" + username + "' AND password = '" + password + "'";

    if (mysql_query(connection, query.c_str()) != 0) {
        std::cerr << "Query execution error: " << mysql_error(connection) << std::endl;
        return false;
    }

    MYSQL_RES* result = mysql_store_result(connection);
    if (result == nullptr) {
        std::cerr << "Error retrieving result set: " << mysql_error(connection) << std::endl;
        return false;
    }

    bool isAdminValid = (mysql_num_rows(result) == 1);

    mysql_free_result(result);

    return isAdminValid;
}

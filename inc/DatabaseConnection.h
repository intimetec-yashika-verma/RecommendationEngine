#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

#include <mysql/mysql.h>
#include <stdexcept>

class DatabaseConnection {
private:
    static DatabaseConnection* instance;
    MYSQL* connection;
    const char* host;
    const char* user;
    const char* password;
    const char* database;

    // Private constructor to prevent instantiation
    DatabaseConnection();

    // Private copy constructor and assignment operator to prevent copying
    DatabaseConnection(const DatabaseConnection&) = delete;
    DatabaseConnection& operator=(const DatabaseConnection&) = delete;

public:
    // Static method to get the single instance of the class
    static DatabaseConnection* getInstance();

    // Method to get the MySQL connection
    MYSQL* getConnection();

    // Destructor to clean up the connection
    ~DatabaseConnection();
};

#endif // DATABASECONNECTION_H

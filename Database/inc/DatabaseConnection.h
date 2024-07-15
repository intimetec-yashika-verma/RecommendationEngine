#pragma once
#include <mysql/mysql.h>
#include <stdexcept>

class DatabaseConnection
{
private:
    static DatabaseConnection *instance;
    MYSQL *connection;
    const char *host;
    const char *user;
    const char *password;
    const char *database;

    DatabaseConnection();


    DatabaseConnection(const DatabaseConnection &) = delete;
    DatabaseConnection &operator=(const DatabaseConnection &) = delete;

public:
    static DatabaseConnection *getInstance();
    MYSQL *getConnection();
    ~DatabaseConnection();
};



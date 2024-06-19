#ifndef ADMIN_DAO_H
#define ADMIN_DAO_H

#include <mysql/mysql.h>
#include <string>
#include <iostream>
#include "DatabaseConnection.h"

class UserDao {
public:
    
private:
    MYSQL* connection;

    void initConnection();
};

#endif // ADMIN_DAO_H

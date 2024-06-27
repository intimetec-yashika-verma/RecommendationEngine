
#pragma once
#include <string>
#include "DatabaseConnection.h"

class AuthenticationService {
public:
    AuthenticationService(DatabaseConnection * connection);
    ~AuthenticationService();
    
    bool authenticateUser(std::vector<std::string> userCredentials);

private:
   DatabaseConnection *connection;
};

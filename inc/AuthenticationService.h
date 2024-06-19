#ifndef AuthenticatonService_H
#define AuthenticatonService_H

#include <string>

class AuthenticationService {
public:
    AuthenticationService();
    ~AuthenticationService();

    bool authenticateUser(const std::string& username, const std::string& password);

private:
   
};

#endif // AuthenticatonService_H

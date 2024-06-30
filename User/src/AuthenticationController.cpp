#include "AuthenticationController.h"
#include "RequestSerializer.h"
#include <utility>
#include "Login.h"

AuthenticationController::AuthenticationController(UserService *userService)
: userService(userService) {}

int AuthenticationController::authenticateUser(std::vector<std::string> userData)
{

    Login userCredentials = RequestSerializer::deserializeLoginCredentials(userData);
    std::cout<<userCredentials.userName<<" "<<userCredentials.password<<std::endl;
    int role = userService->authenticateUser(userCredentials.userName,userCredentials.password);
    std::cout<<"role "<<role<<std::endl;
   return role;
}

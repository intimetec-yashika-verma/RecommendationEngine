#include "AuthenticationController.h"
#include <utility>
#include "LoginCredential.h"
#include "UserProfile.h"

AuthenticationController::AuthenticationController(UserService *userService)
    : userService(userService) {}

UserProfile AuthenticationController::authenticateUser(std::string userData)
{

    LoginCredential loginCredentials;
    loginCredentials.deserialize(userData);
    UserProfile userProfile = userService->authenticateUser(loginCredentials.emailId, loginCredentials.password);
    return userProfile;
}

#pragma once
#include <iostream>
struct User
{
    std::string id;
    std::string email;
    std::string password;
    int role;

    User(std::string userId, std::string email, std::string password,int role)
        : id(userId), email(email), password(password), role(role) {}
};
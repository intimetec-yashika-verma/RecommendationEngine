#pragma once
#include <iostream>
#include <vector>
#include "Operation.h"
class IUserController
{
public:
    virtual std::vector<std::string> handleRequest(std::pair<Operation, std::vector<std::string>> userRequest) = 0;
};
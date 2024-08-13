#pragma once
#include <iostream>
#include <vector>
#include "Operation.h"
class IUserController
{
public:
    virtual std::string handleRequest(std::pair<Operation, std::string> userRequest) = 0;
};
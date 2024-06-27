#pragma once
#include<iostream>
#include<vector>
class StringSerializer {
public:
    std::string serialize(std::vector<std::string> data);
    std::vector<std::string> deserialize(const std::string& data);
};
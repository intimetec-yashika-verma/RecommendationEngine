#pragma once
#include<iostream>
#include<vector>
class StringSerializer {
public:
    static std::string serialize(std::vector<std::string> data);
    static std::vector<std::string> deserialize(const std::string& data);
};
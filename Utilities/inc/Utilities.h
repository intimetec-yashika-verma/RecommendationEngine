#pragma once

#include "../inc/Utilities.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <unordered_set>

class Utilities
{
public:
   static std::string toLower(const std::string &str);

   static std::vector<std::string> splitWords(const std::string &str);

   static std::unordered_set<std::string> readWordsFromFile(const std::string &filename);
   static std::vector<std::string> splitFeedback(const std::string &s);
};
#include <iostream>
#include <unordered_map>
#include "Feedback.h"
#
class Serializer
{
public:
static std::string serializeFeedbacks(const std::unordered_map<std::string, Feedback>& feedbacks);
static std::string serializeMenuItems(const MenuItem& menuItem);
};
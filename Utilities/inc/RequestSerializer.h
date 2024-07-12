#include <utility>
#include <iostream>
#include <vector>
#include "Operation.h"
#include "MenuItem.h"
class RequestSerializer
{
  public:
  static std::pair<Operation, std::string> deserializeOperation(const std::string& userCredentials);
  static MenuItem deserializeMenuItems(std::vector<std::string> ItemsData);
  static std::vector<std::string> serializeMenuItemToString(std::vector<MenuItem> menuItems);
};

#include <utility>
#include <iostream>
#include <vector>
#include "Operation.h"
#include "Login.h"
#include "MenuItem.h"
class RequestSerializer
{
  public:
  static std::pair<Operation, std::vector<std::string>> deserializeOperation(std::vector<std::string> userCredentials);
  static Login deserializeLoginCredentials(std::vector<std::string> userCredentials);
  static MenuItem deserializeMenuItems(std::vector<std::string> ItemsData);
  static std::vector<std::string> serializeMenuItemToString(std::vector<MenuItem> menuItems);
};

#pragma once
#include <iostream>
#include <vector>
#include "DatabaseConnection.h"
class PublishedMenuDAO
{
public:
PublishedMenuDAO();
  void addItems(std::string itemList);

private:
  DatabaseConnection *dbConnection;
  MYSQL *connection;
};
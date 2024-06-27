#pragma once
#include <iostream>
#include <vector>
#include "Server.h"
class ClientSession
{
public:
  ClientSession(int clientSocket,Server *server);
  int startSession();
  int clientSocket;
  Server *server;


private:
  int sessionId;
  int clientRole;
  std::vector<std::string> takeUserCredentials();
  std::string fetchRolefromMail(std::string response);
  int validateRole(std::string role);
  bool handleUser();
};
#pragma once
#include<iostream>
class Session
{
public:
  int sessionId;
  int userRole;
  bool startSession(int ClientSocket);
  std::string getRolefromMail(std::string response);
  int validateRole(std::string role);
  bool handleUser();
};
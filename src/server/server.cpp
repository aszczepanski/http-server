#include "server/server.h"
#include <iostream>

using server::Server;
using std::cout;
using std::endl;

Server::Server() {
}

void Server::run() {
  cout << "Server running" << endl;
}

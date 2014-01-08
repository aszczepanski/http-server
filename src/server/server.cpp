#include "server/server.h"
#include <string>
#include <iostream>
#include <libconfig.h++>

using server::Server;
using std::cout;
using std::endl;

Server::Server(const libconfig::Config& config) {
  config.lookupValue("address", address);
  config.lookupValue("port", port);
  cout << "address: " << address << endl;
  cout << "port: " << port << endl;
}

void Server::run() {
  cout << "Server running" << endl;
}

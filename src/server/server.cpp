#include "server/server.h"

#include <string>
#include <iostream>
#include <memory>
#include <libconfig.h++>

#include "server/connection_manager.h"
#include "server/request_handler.h"
#include "server/acceptor.h"
#include "server/socket.h"

using server::Server;
using std::cout;
using std::endl;
using std::unique_ptr;

Server::Server(const libconfig::Config& config)
  : connection_manager_(),
    request_handler_(config),
    acceptor_() {
  config.lookupValue("address", address);
  config.lookupValue("port", port);
  cout << "address: " << address << endl;
  cout << "port: " << port << endl;

  acceptor_.Open();
  acceptor_.ReuseAddress(true);
  acceptor_.Bind(port);
  acceptor_.Listen();
}

void Server::Run() {
  cout << "Server running" << endl;

  // accept
  unique_ptr<Socket> socket = std::move(acceptor_.Accept());
}

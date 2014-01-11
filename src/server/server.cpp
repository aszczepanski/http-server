#include "server/server.h"

#include <string>
#include <iostream>
#include <memory>
#include <libconfig.h++>

#include "server/connection_manager.h"
#include "server/request_handler.h"
#include "server/acceptor.h"
#include "server/socket.h"
#include "logger/logger.h"

using server::Server;
using std::cout;
using std::endl;
using std::unique_ptr;

logger::Logger Server::logger_("server.server");

Server::Server(const libconfig::Config& config)
  : connection_manager_(),
    request_handler_(config),
    acceptor_() {
  config.lookupValue("address", address);
  config.lookupValue("port", port);
  LOG_INFO(logger_, "Address: " << address)
  LOG_INFO(logger_, "Port: " << port)

  acceptor_.Open();
  acceptor_.ReuseAddress(true);
  acceptor_.Bind(port);
  acceptor_.Listen();
}

void Server::Run() {
  LOG_INFO(logger_, "Server is running")

  // accept
  unique_ptr<Socket> socket = std::move(acceptor_.Accept());
}

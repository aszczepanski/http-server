#include "server/server.h"

#include <string>
#include <iostream>
#include <memory>
#include <libconfig.h++>
#include <signal.h>
#include <set>

#include "server/connection_manager.h"
#include "server/request_handler.h"
#include "server/acceptor.h"
#include "server/socket.h"
#include "logger/logger.h"

using server::Server;
using std::cout;
using std::endl;
using std::unique_ptr;
using std::set;

const logger::Logger Server::logger_("server.server");
set<Server*> Server::instances_;

void Server::SignalHandler() {
  acceptor_.Close();
  connection_manager_.StopAll();
}

void Server::StaticSignalHandler(int signum) {
  LOG_INFO(Server::logger_, "Signal: " << signum)
  for (auto item : Server::instances_) {
    item->SignalHandler();
  }
}

Server::~Server() {
  instances_.erase(this);
}

Server::Server(const libconfig::Config& config)
  : connection_manager_(),
    request_handler_(config),
    acceptor_() {
  // read configuration
  config.lookupValue("address", address);
  config.lookupValue("port", port);
  LOG_INFO(logger_, "Address: " << address)
  LOG_INFO(logger_, "Port: " << port)

  // init acceptor
  acceptor_.Open();
  acceptor_.ReuseAddress(true);
  acceptor_.Bind(port);
  acceptor_.Listen();

  // register signals
  instances_.insert(this);
  signal(SIGINT, StaticSignalHandler);
  signal(SIGTERM, StaticSignalHandler);
}

void Server::Run() {
  LOG_INFO(logger_, "Server is running")

  // accept
  unique_ptr<Socket> socket = std::move(acceptor_.Accept());
  connection_manager_.Start(std::make_shared<Connection>(
    std::move(socket), request_handler_));
}

#include "server/server.h"

#include <string>
#include <iostream>
#include <memory>
#include <signal.h>
#include <set>

#include "server/connection_manager.h"
#include "server/request_handler.h"
#include "server/acceptor.h"
#include "server/socket.h"
#include "server/acceptor_exceptions.h"
#include "logger/logger.h"
#include "settings/settings.h"

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

Server::Server()
  : connection_manager_(),
    request_handler_(),
    acceptor_() {
  // read configuration
  settings::Settings& settings = settings::Settings::getSettings();
  address = settings.GetValue<std::string>("address");
  port = settings.GetValue<std::string>("port");
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
  while (true) {
    try {
      unique_ptr<Socket> socket = std::move(acceptor_.Accept());
      connection_manager_.Start(std::make_shared<Connection>(
       std::move(socket), request_handler_, &connection_manager_));
    }
    catch (...) {
      LOG_ERROR(logger_, "exception")
      break;
    }
  }
}

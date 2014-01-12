#include "server/connection_manager.h"
#include "server/connection.h"
#include <set>

using server::ConnectionManager;
using server::Connection;

const logger::Logger ConnectionManager::logger_("server.connection_manager");

ConnectionManager::ConnectionManager() {
}

void ConnectionManager::Start(std::shared_ptr<Connection> connection) {
  connections_.insert(connection);
  connection->Run();
}

void ConnectionManager::Stop(std::shared_ptr<Connection> connection) {
  connections_.erase(connection);
  connection->Stop();
}

void ConnectionManager::StopAll() {
  for (auto c : connections_) {
    c->Stop();
  }
  connections_.clear();
}

#include "server/connection_manager.h"
#include "server/connection.h"
#include <set>

using server::ConnectionManager;
using server::Connection;

const logger::Logger ConnectionManager::logger_("server.connection_manager");

ConnectionManager::ConnectionManager() {
}

void ConnectionManager::Start(std::shared_ptr<Connection> connection) {
  // TODO(adam): start connection
  connections_.insert(connection);
  connection->Run();

  connection->Wait();  // TODO(adam): remove
}

void ConnectionManager::Stop(std::shared_ptr<Connection> connection) {
  // TODO(adam): stop connection
  connections_.erase(connection);
}

void ConnectionManager::StopAll() {
  for (auto c : connections_) {
    // TODO(adam): stop connection
  }
  connections_.clear();
}

#include "server/connection_manager.h"
#include "server/connection.h"
#include <set>

using server::ConnectionManager;
using server::Connection;

ConnectionManager::ConnectionManager() {
}

void ConnectionManager::Start(std::shared_ptr<Connection> connection) {
  // TODO(adam): start connection
  connections_.insert(connection);
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

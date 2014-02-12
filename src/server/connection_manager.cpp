#include "server/connection_manager.h"
#include "server/connection.h"
#include <set>

using server::ConnectionManager;
using server::Connection;

const logger::Logger ConnectionManager::logger_("server.connection_manager");

ConnectionManager::ConnectionManager() {
}

void ConnectionManager::Start(std::shared_ptr<Connection> connection) {
  mutex_.Lock();
  connections_.insert(connection);
  mutex_.Unlock();
  connection->Run();
}

void ConnectionManager::Stop(std::shared_ptr<Connection> connection) {
  mutex_.Lock();
  connections_.erase(connection);
  mutex_.Unlock();
  connection->Stop();
}

void ConnectionManager::StopAll() {
  for (auto c : connections_) {
    c->Stop();
  }
  mutex_.Lock();
  connections_.clear();
  mutex_.Unlock();
}

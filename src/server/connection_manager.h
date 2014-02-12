#ifndef SRC_SERVER_CONNECTION_MANAGER_H_
#define SRC_SERVER_CONNECTION_MANAGER_H_

#include <set>
#include <memory>

#include "server/connection.h"
#include "logger/logger.h"
#include "thread/mutex.h"

namespace server {

class ConnectionManager {
 public:
  ConnectionManager();

  void Start(std::shared_ptr<Connection> connection);
  void Stop(std::shared_ptr<Connection> connection);
  void StopAll();

 private:
  std::set<std::shared_ptr<Connection>> connections_;

  mutable thread::Mutex mutex_;
  static const logger::Logger logger_;
};

}  // namespace server

#endif  // SRC_SERVER_CONNECTION_MANAGER_H_

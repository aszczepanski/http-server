#ifndef SRC_SERVER_CONNECTION_H_
#define SRC_SERVER_CONNECTION_H_

#include <memory>

#include "thread/thread_interface.h"
#include "server/socket.h"
#include "logger/logger.h"

namespace server {

class RequestHandler;
class ConnectionManager;

class Connection : public thread::ThreadInterface {
 public:
  explicit Connection(std::unique_ptr<Socket> socket,
    const RequestHandler& request_handler, ConnectionManager* connection_manager);
  void Stop();

 private:
  virtual void* StartRoutine();

  std::unique_ptr<Socket> socket_;
  const RequestHandler& request_handler_;
  ConnectionManager* connection_manager_;

  static const logger::Logger logger_;
};

}  // namespace server

#endif  // SRC_SERVER_CONNECTION_H_

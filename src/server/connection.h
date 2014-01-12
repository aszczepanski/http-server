#ifndef SRC_SERVER_CONNECTION_H_
#define SRC_SERVER_CONNECTION_H_

#include <memory>

#include "thread/thread_interface.h"
#include "server/socket.h"
#include "server/request_handler.h"
#include "logger/logger.h"

namespace server {

class Connection : public thread::ThreadInterface {
 public:
  explicit Connection(std::unique_ptr<Socket> socket, const RequestHandler& request_handler);
  void Stop();

 private:
  virtual void* StartRoutine();

  std::unique_ptr<Socket> socket_;
  const RequestHandler& request_handler_;

  static const logger::Logger logger_;
};

}  // namespace server

#endif  // SRC_SERVER_CONNECTION_H_

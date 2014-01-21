#ifndef SRC_SERVER_CONNECTION_H_
#define SRC_SERVER_CONNECTION_H_

#include <memory>

#include "thread/thread_interface.h"
#include "server/socket.h"
#include "server/request_parser.h"
#include "logger/logger.h"
#include "http/request.h"
#include "http/response.h"

namespace server {

class RequestHandler;
class ConnectionManager;

class Connection : public thread::ThreadInterface, public std::enable_shared_from_this<Connection> {
 public:
  explicit Connection(std::unique_ptr<Socket> socket,
    const RequestHandler& request_handler, ConnectionManager* connection_manager);
  void Stop();

 private:
  virtual void* StartRoutine();

  void CreateResponse(RequestParser::ParseResult res);
  void WriteResponse();

  std::unique_ptr<Socket> socket_;
//  RequestParser request_parser_;
  const RequestHandler& request_handler_;
  ConnectionManager* connection_manager_;

  http::Request request_;
  http::Response response_;

  bool persistent_connection_;
  int timeout_seconds_;
  int timeout_microseconds_;

  static const logger::Logger logger_;
};

}  // namespace server

#endif  // SRC_SERVER_CONNECTION_H_

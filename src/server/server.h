#ifndef SRC_SERVER_SERVER_H_
#define SRC_SERVER_SERVER_H_

#include <libconfig.h++>
#include <string>
#include "server/connection_manager.h"
#include "server/request_handler.h"
#include "server/acceptor.h"

namespace server {

class Server {
 public:
  explicit Server(const libconfig::Config& config);

  void Run();
 private:
  std::string address;
  std::string port;

  ConnectionManager connection_manager_;
  RequestHandler request_handler_;
  Acceptor acceptor_;
};

}  // namespace server

#endif  // SRC_SERVER_SERVER_H_

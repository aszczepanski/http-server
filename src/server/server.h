#ifndef SRC_SERVER_SERVER_H_
#define SRC_SERVER_SERVER_H_

#include <string>
#include <set>

#include "server/connection_manager.h"
#include "server/request_handler.h"
#include "server/acceptor.h"
#include "logger/logger.h"

namespace server {

class Server {
 public:
  Server();
  ~Server();

  void Run();
 private:
  std::string address;
  std::string port;

  ConnectionManager connection_manager_;
  RequestHandler request_handler_;
  Acceptor acceptor_;

  static void StaticSignalHandler(int signum);
  void SignalHandler();

  static std::set<Server*> instances_;  // rly bad solution

  static const logger::Logger logger_;
};

}  // namespace server

#endif  // SRC_SERVER_SERVER_H_

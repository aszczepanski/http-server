#ifndef SRC_SERVER_SERVER_H_
#define SRC_SERVER_SERVER_H_

#include <libconfig.h++>
#include <string>
#include "server/connection_manager.h"

namespace server {

class Server {
 public:
  explicit Server(const libconfig::Config& config);

  void Run();
 private:
  std::string address;
  std::string port;

  ConnectionManager connection_manager_;
};

}  // namespace server

#endif  // SRC_SERVER_SERVER_H_

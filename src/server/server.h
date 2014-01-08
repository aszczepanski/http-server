#ifndef SRC_SERVER_SERVER_H_
#define SRC_SERVER_SERVER_H_

#include <libconfig.h++>
#include <string>

namespace server {

class Server {
 public:
  explicit Server(const libconfig::Config& config);

  void run();
 private:
  std::string address;
  std::string port;
};

}  // namespace server

#endif  // SRC_SERVER_SERVER_H_

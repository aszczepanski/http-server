#ifndef SRC_SERVER_SOCKET_H_
#define SRC_SERVER_SOCKET_H_

namespace server {

class Socket {
 public:
  explicit Socket(int sock_fd);

 private:
  const int sock_fd_;
};

}  // namespace server

#endif  // SRC_SERVER_SOCKET_H_

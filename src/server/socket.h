#ifndef SRC_SERVER_SOCKET_H_
#define SRC_SERVER_SOCKET_H_

#include <cstddef>

namespace server {

class Socket {
 public:
  explicit Socket(int sock_fd);

  // blocks, returns number of bytes read
  size_t Read(void* array, std::size_t max_bytes_count);

  void Write(const void* array, std::size_t bytes_count);

 private:
  const int sock_fd_;
};

}  // namespace server

#endif  // SRC_SERVER_SOCKET_H_

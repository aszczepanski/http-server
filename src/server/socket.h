#ifndef SRC_SERVER_SOCKET_H_
#define SRC_SERVER_SOCKET_H_

#include <cstddef>

#include "logger/logger.h"

namespace server {

// TODO(adam): handle broken pipe

class Socket {
 public:
  explicit Socket(int sock_fd);

  // blocks, returns number of bytes read
  size_t Read(void* array, std::size_t max_bytes_count);
  // blocks, waits max tv_sec seconds and tv_usec microseconds
  // returns number of bytes read
  size_t Read(void* array, std::size_t max_bytes_count, int tv_sec, int tv_usec);

  void Write(const void* array, std::size_t bytes_count);

  void Close();

  static const size_t kMaxBufferSize = 8192;

 private:
  const int sock_fd_;

  static const logger::Logger logger_;
};

}  // namespace server

#endif  // SRC_SERVER_SOCKET_H_

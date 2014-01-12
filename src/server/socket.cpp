#include "server/socket.h"

#include <cstdio>
#include <cstddef>
#include <cstring>
#include <unistd.h>
#include <errno.h>

#include "logger/logger.h"

using server::Socket;

const logger::Logger Socket::logger_("server.socket");

Socket::Socket(int sock_fd)
  : sock_fd_(sock_fd) {
}

std::size_t Socket::Read(void* array, std::size_t max_bytes_count) {
  int status = read(sock_fd_, array, max_bytes_count);
  if (status == -1) {
    LOG_ERROR(logger_, "Read error: " << strerror(errno))
    // TODO(adam): exception
  }
  return status;
}

void Socket::Write(const void* array, std::size_t bytes_count) {
  int status = write(sock_fd_, array, bytes_count);
  if (status == -1) {
    LOG_ERROR(logger_, "Write error: " << strerror(errno))
    // TODO(adam): exception
  }
}

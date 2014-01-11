#include "server/socket.h"

#include <cstdio>
#include <cstddef>
#include <unistd.h>

using server::Socket;

Socket::Socket(int sock_fd)
  : sock_fd_(sock_fd) {
}

std::size_t Socket::Read(void* array, std::size_t max_bytes_count) {
  int status = read(sock_fd_, array, max_bytes_count);
  if (status == -1) {
    perror("read error");
    // TODO(adam): exception
  }
  return status;
}

void Socket::Write(const void* array, std::size_t bytes_count) {
  int status = write(sock_fd_, array, bytes_count);
  if (status == -1) {
    perror("write error");
    // TODO(adam): exception
  }
}

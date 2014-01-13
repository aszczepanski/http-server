#include "server/socket.h"

#include <cstdio>
#include <cstddef>
#include <cstring>
#include <unistd.h>
#include <errno.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/time.h>

#include "logger/logger.h"
#include "server/socket_exceptions.h"

using server::Socket;

const logger::Logger Socket::logger_("server.socket");

Socket::Socket(int sock_fd)
  : sock_fd_(sock_fd) {
}

std::size_t Socket::Read(void* array, std::size_t max_bytes_count) {
  int status = read(sock_fd_, array, max_bytes_count);
  if (status == -1) {
    LOG_ERROR(logger_, "Read error: " << strerror(errno))
    throw ReadError(strerror(errno));
  }
  return status;
}

std::size_t Socket::Read(void* array, std::size_t max_bytes_count, int tv_sec, int tv_usec) {
  // TODO(adam): tests
  fd_set masterfds, readfds;
  FD_ZERO(&masterfds);
  FD_SET(sock_fd_, &masterfds);
  memcpy(&readfds, &masterfds, sizeof(fd_set));
  timeval timeout;
  timeout.tv_sec = tv_sec;
  timeout.tv_usec = tv_usec;
  if (select(sock_fd_+1, &readfds, NULL, NULL, &timeout) < 0) {
    LOG_ERROR(logger_, "Select error: " << strerror(errno))
    throw SelectError(strerror(errno));
  }

  int status;
  if (FD_ISSET(sock_fd_, &readfds)) {
    status = read(sock_fd_, array, max_bytes_count);
    if (status == -1) {
      LOG_ERROR(logger_, "Read error: " << strerror(errno))
      perror("server read error");
      throw ReadError(strerror(errno));
    }
  } else {
    LOG_ERROR(logger_, "Read error: timedout")
    throw SelectError("timedout");
  }
  return status;
}

void Socket::Write(const void* array, std::size_t bytes_count) {
  int status = write(sock_fd_, array, bytes_count);
  if (status == -1) {
    LOG_ERROR(logger_, "Write error: " << strerror(errno))
    throw WriteError(strerror(errno));
  }
}

void Socket::Close() {
  close(sock_fd_);
  LOG_DEBUG(logger_, "Socket closed")
}

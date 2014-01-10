#include "server/socket.h"

using server::Socket;

Socket::Socket(int sock_fd)
  : sock_fd_(sock_fd) {
}

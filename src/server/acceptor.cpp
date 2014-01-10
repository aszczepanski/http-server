#include "server/acceptor.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <iostream>
#include <string>
#include <memory>

#include "server/socket.h"

using server::Acceptor;
using server::Socket;
using std::cout;
using std::cerr;
using std::endl;

Acceptor::Acceptor() {
}

void Acceptor::Open() {
  sock_fd_ = socket(AF_INET, SOCK_STREAM, 0);
  if (sock_fd_ == -1) {
    perror("socket open error");
    // TODO(adam): exception
  }
}

void Acceptor::Bind(const std::string& port) {
  port_ = port;

  sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(atoi(port.c_str()));
  addr.sin_addr.s_addr = INADDR_ANY;  // TODO(adam): make it configurable

  if (bind(sock_fd_, (sockaddr*)&addr, sizeof(addr)) == -1) {
    perror("bind error");
    // TODO(adam): exception
  }
}

void Acceptor::Listen() {
  if (listen(sock_fd_, kListenBacklog) == -1) {
    perror("listen error");
    // TODO(adam): exception
  }
}

void Acceptor::ReuseAddress(bool reuse_address) {
  char iOption;
  if (reuse_address) {
    iOption = 1;
    if (setsockopt(sock_fd_, SOL_SOCKET, SO_REUSEADDR, &iOption,  sizeof(int)) == -1) {
      perror("set reuse address error");
      // TODO(adam): exception
    }
  } else {
    iOption = 0;
    if (setsockopt(sock_fd_, SOL_SOCKET, SO_REUSEADDR, &iOption,  sizeof(int)) == -1) {
      perror("clear reuse address error");
      // TODO(adam): exception
    }
  }
}

std::unique_ptr<server::Socket> Acceptor::Accept() {
  std::cout << "ACCEPTOR waiting for socket" << std::endl;

  socklen_t socklen;
  sockaddr_in in_addr;
  socklen = sizeof(in_addr);

  int new_sock_fd = accept(sock_fd_, (sockaddr*)&in_addr, &socklen);
  if (new_sock_fd == -1) {
    perror("accept error");
    // TODO(adam): exception
  }

  return std::unique_ptr<server::Socket>(new server::Socket(new_sock_fd));
}

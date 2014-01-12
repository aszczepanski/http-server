#include "server/connection.h"

#include <memory>
#include <iostream>
#include <string>

#include "server/socket.h"
#include "server/request_handler.h"
#include "logger/logger.h"

using server::Connection;

const logger::Logger Connection::logger_("server.connection");

Connection::Connection(std::unique_ptr<Socket> socket, const RequestHandler& request_handler)
  : socket_(std::move(socket)),
    request_handler_(request_handler) {
  LOG_DEBUG(logger_, "Creating connection")
}

void* Connection::StartRoutine() {
  LOG_DEBUG(logger_, "Starting connection")

  char buffer[8192];
  size_t bytes_read = socket_->Read(buffer, 8192);

  LOG_DEBUG(logger_, "Received data: \n" << std::string(buffer, bytes_read))

  return nullptr;
}

void Connection::Stop() {
}

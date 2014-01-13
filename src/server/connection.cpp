#include "server/connection.h"

#include <memory>
#include <iostream>
#include <string>

#include "server/socket.h"
#include "server/request_handler.h"
#include "server/request_parser.h"
#include "server/connection_manager.h"
#include "logger/logger.h"
#include "http/request.h"
#include "http/reply.h"

using server::Connection;
using server::RequestParser;

const logger::Logger Connection::logger_("server.connection");

Connection::Connection(std::unique_ptr<Socket> socket,
  const RequestHandler& request_handler, ConnectionManager* connection_manager)
  : socket_(std::move(socket)),
    request_parser_(),
    request_handler_(request_handler),
    connection_manager_(connection_manager) {
  LOG_DEBUG(logger_, "Creating connection")
}

void* Connection::StartRoutine() {
  LOG_DEBUG(logger_, "Starting connection")

  http::Request request;
  RequestParser::ParseResult res;

  do {
    char buffer[Socket::kMaxBufferSize];
    size_t bytes_read = socket_->Read(buffer, Socket::kMaxBufferSize);

    LOG_DEBUG(logger_, "Received data: \n" << std::string(buffer, bytes_read))
    res = request_parser_.Parse(buffer, bytes_read, &request);
  } while (res == RequestParser::kUnknown);

  http::Reply reply;

  if (res == RequestParser::kGood) {
    request_handler_.HandleRequest(request, &reply);
  } else if (res == RequestParser::kBad) {
  }

  // TODO(adam): stop this in connection manager

  return nullptr;
}

void Connection::Stop() {
  socket_->Close();
}

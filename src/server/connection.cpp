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

  RequestParser::ParseResult res;

  do {
    char buffer[Socket::kMaxBufferSize];
    // TODO(adam): catch exceptions
    size_t bytes_read = socket_->Read(buffer, Socket::kMaxBufferSize);

    LOG_DEBUG(logger_, "Received data: \n" << std::string(buffer, bytes_read))
    res = request_parser_.Parse(buffer, bytes_read, &request_);
  } while (res == RequestParser::kUnknown);

  if (res == RequestParser::kGood) {
    request_handler_.HandleRequest(request_, &reply_);
    WriteReply();
  } else if (res == RequestParser::kBad) {
    reply_ = http::Reply::StockReply(http::Reply::StatusType::bad_request);
    WriteReply();
  }

  // TODO(adam): stop this in connection manager

  return nullptr;
}

void Connection::Stop() {
  socket_->Close();
}

void Connection::WriteReply() {
  std::string reply_string = reply_.ToString();
  socket_->Write(reply_string.c_str(), reply_string.size());
}

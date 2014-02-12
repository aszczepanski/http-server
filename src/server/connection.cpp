#include "server/connection.h"

#include <memory>
#include <iostream>
#include <string>
#include <cassert>

#include "server/socket.h"
#include "server/request_handler.h"
#include "server/request_parser.h"
#include "server/connection_manager.h"
#include "logger/logger.h"
#include "http/request.h"
#include "http/response.h"
#include "settings/settings.h"

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
  settings::Settings& settings = settings::Settings::getSettings();
  persistent_connection_ = settings.GetValue<bool>("persistent_connection");
  timeout_do_ = settings.GetValue<bool>("timeout.do");
  if (timeout_do_) {
    timeout_seconds_ = settings.GetValue<int>("timeout.seconds");
    timeout_microseconds_ = settings.GetValue<int>("timeout.microseconds");
  }
}

void Connection::CreateResponse(RequestParser::ParseResult res) {
  if (res == RequestParser::GOOD) {
    request_handler_.HandleRequest(request_, &response_);
    WriteResponse();
  } else if (res == RequestParser::BAD) {
    response_ = http::Response::StockResponse(http::Response::Status::BAD_REQUEST);
    WriteResponse();
  } else if (res == RequestParser::UNKNOWN) {
    assert(false);
  } else {
    return;
  }
}

RequestParser::ParseResult Connection::GetRequest() {
  RequestParser::ParseResult res;
  char buffer[Socket::kMaxBufferSize];

  do {
    try {
      size_t bytes_read;
      if (timeout_do_) {
        LOG_DEBUG(logger_, "here")
        assert(timeout_seconds_ > 0 || timeout_microseconds_ > 0);
        bytes_read = socket_->Read(
            buffer, Socket::kMaxBufferSize, timeout_seconds_, timeout_microseconds_);
      } else {
        bytes_read = socket_->Read(buffer, Socket::kMaxBufferSize);
      }
      if (bytes_read == 0) {
        LOG_WARN(logger_, "0 bytes read")
        res = RequestParser::END_CONNECTION;
        break;
      }

      res = request_parser_.Parse(buffer, bytes_read, &request_);
    } catch (...) {
      res = RequestParser::END_CONNECTION;
      break;
    }
    if (res == RequestParser::UNKNOWN) LOG_DEBUG(logger_, "UNKNOWN");
  } while (res == RequestParser::UNKNOWN);

  return res;
}

void* Connection::StartRoutine() {
  LOG_DEBUG(logger_, "Starting connection")

  RequestParser::ParseResult res;

  if (!persistent_connection_) {
    res = GetRequest();
    CreateResponse(res);

  } else {
    do {
      res = GetRequest();
      CreateResponse(res);
    } while (res == RequestParser::GOOD);
  }

  connection_manager_->Stop(shared_from_this());

  return nullptr;
}

void Connection::Stop() {
  socket_->Close();
}

void Connection::WriteResponse() {
  std::string response_string = response_.ToString();
  socket_->Write(response_string.c_str(), response_string.size());
}

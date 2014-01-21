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
//    request_parser_(),
    request_handler_(request_handler),
    connection_manager_(connection_manager) {
  LOG_DEBUG(logger_, "Creating connection")
  settings::Settings& settings = settings::Settings::getSettings();
  persistent_connection_ = settings.GetValue<bool>("persistent_connection");
  if (persistent_connection_) {
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

void* Connection::StartRoutine() {
  LOG_DEBUG(logger_, "Starting connection")

  RequestParser::ParseResult res;

  char buffer[Socket::kMaxBufferSize];

  if (!persistent_connection_) {
    do {
      try {
        size_t bytes_read = socket_->Read(buffer, Socket::kMaxBufferSize);
        if (bytes_read == 0) {
          res = RequestParser::END_CONNECTION;
          break;
        }

        LOG_DEBUG(logger_, "Received data: \n" << std::string(buffer, bytes_read))
    //    res = request_parser_.Parse(buffer, bytes_read, &request_);
        res = RequestParser::GOOD;
        request_.method() = http::Request::GET;
        request_.uri() = "/index.html";
      } catch (...) {
        res = RequestParser::END_CONNECTION;
        break;
      }
    } while (res == RequestParser::UNKNOWN);

    CreateResponse(res);

  } else {
    do {
      do {
        try {
          assert(timeout_seconds_ > 0 || timeout_microseconds_ > 0);
          size_t bytes_read = socket_->Read(buffer, Socket::kMaxBufferSize);
          if (bytes_read == 0) {
            res = RequestParser::END_CONNECTION;
            break;
          }

          LOG_DEBUG(logger_, "Received data: \n" << std::string(buffer, bytes_read))
      //    res = request_parser_.Parse(buffer, bytes_read, &request_);
          res = RequestParser::GOOD;
          request_.method() = http::Request::GET;
          request_.uri() = "/index.html";
        } catch (...) {
          res = RequestParser::END_CONNECTION;
          break;
        }
      } while (res == RequestParser::UNKNOWN);

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

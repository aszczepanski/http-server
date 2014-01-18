#include "server/request_parser.h"

#include "http/request.h"
#include "logger/logger.h"

using server::RequestParser;

const logger::Logger RequestParser::logger_("server.request_parser");

RequestParser::ParseResult RequestParser::Parse(
    const char* buffer, size_t bytes_read, http::Request* request) {
  // TODO(pewniak): parse
  int cursor = 0;
  while (cursor < bytes_read) {
    switch (state_) {
      case REQUEST_LINE:
        state_ = ERROR;  // TODO(pewniak) parse request line
        break;
      case ERROR:
        cursor++;  // TODO(pewniak) move until end of request
        break;
      default:
        state_ = ERROR;
    }
  }

  if (state_ == ERROR) {
    return RequestParser::BAD;
  } else if (state_ == SUCCESS) {
    return RequestParser::GOOD;
  } else {
    return RequestParser::UNKNOWN;
  }
}

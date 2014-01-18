#include "server/request_parser.h"

#include "http/request.h"
#include "logger/logger.h"

#include<string>

using server::RequestParser;

const logger::Logger RequestParser::logger_("server.request_parser");

RequestParser::ParseResult RequestParser::Parse(
    const char* buffer, size_t bytes_read, http::Request* request) {
  // TODO(pewniak): parse
  size_t cursor = 0;
  while (cursor < bytes_read) {
    std::string line = GetLine(buffer + cursor);
    switch (state_) {
      case REQUEST_LINE:
        state_ = ERROR;  // TODO(pewniak) parse request line
        break;
      case ERROR:
        break;
      default:
        state_ = ERROR;
        break;
    }
    cursor = cursor + line.length() + delimiter.length();
  }

  if (state_ == ERROR) {
    return RequestParser::BAD;
  } else if (state_ == SUCCESS) {
    return RequestParser::GOOD;
  } else {
    return RequestParser::UNKNOWN;
  }
}

std::string RequestParser::GetLine(const char* buffer) {
  std::string bufferString(buffer);
  size_t occurence = bufferString.find(delimiter);
  if (std::string::npos == occurence) {
    return bufferString;
  } else {
    return bufferString.substr(0, occurence);
  }
}

#include "server/request_parser.h"

#include "http/request.h"
#include "logger/logger.h"

#include<string>

using server::RequestParser;

const logger::Logger RequestParser::logger_("server.request_parser");

RequestParser::ParseResult RequestParser::Parse(
    const char* buffer, size_t bytes_read, http::Request* request) {
  size_t cursor = 0;
  tempBody = "";
  while (cursor < bytes_read) {
    std::string line = GetLine(buffer + cursor);
    cursor = cursor + line.length() + delimiter.length();

    switch (state_) {
      case REQUEST_LINE:
        state_ = HEADERS;  // TODO(pewniak) parse request line
        break;
      case HEADERS:
        if (0 == line.length()) {
          if (cursor >= bytes_read)
            state_ = SUCCESS;
          else
            state_ = BODY;
        } else {
          // TODO(pewniak) parse header
        }
        break;
      case BODY:
        tempBody += line;
        if (cursor >= bytes_read || 0 == line.length()) {
          state_ = SUCCESS;
        }
        break;
      case ERROR:
        break;
      case SUCCESS:
        // TODO(pewniak) handle remaining data
        break;
      default:
        state_ = ERROR;
        break;
    }
  }

  if (state_ == ERROR) {
    return RequestParser::BAD;
  } else if (state_ == SUCCESS) {
    // TODO(pewniak) populate request fields
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

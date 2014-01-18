#include "server/request_parser.h"

#include "http/request.h"
#include "logger/logger.h"

#include<string>
#include<map>
#include<utility>
#include<sstream>

using server::RequestParser;

const logger::Logger RequestParser::logger_("server.request_parser");

RequestParser::ParseResult RequestParser::Parse(
    const char* buffer, size_t bytes_read, http::Request* request) {
  Reset();
  size_t cursor = 0;
  while (cursor < bytes_read) {
    std::string line = GetLine(buffer + cursor);
    cursor = cursor + line.length() + delimiter.length();

    switch (state_) {
      case REQUEST_LINE:
        state_ = HEADERS;  // TODO(pewniak) parse request line
        break;
      case HEADERS:
        if (line.length() > 0) {
          std::pair<std::string, std::string> *header = ParseHeader(line);
          if (header != NULL) {
            tempHeaders.insert(*header);
          } else {
            state_ = ERROR;
          }
        } else {
          if (cursor >= bytes_read)
            state_ = SUCCESS;
          else
            state_ = BODY;
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
    DebugState();
    // TODO(pewniak) populate request fields
    return RequestParser::GOOD;
  } else {
    return RequestParser::UNKNOWN;
  }
}

void RequestParser::Reset() {
  if (state_ != BODY) {
    tempBody = "";
    tempURL = "";
    tempHTTPVersion = "";
    tempHTTPMethod = http::Request::Method::GET;
    state_ = REQUEST_LINE;
    tempHeaders.clear();
  }
}

void RequestParser::DebugState() {
  std::stringstream debug;
  debug << "RESULTS method: " << tempHTTPMethod;
  debug << " URL: " << tempURL;
  debug << " HTTP_VERSION: " << tempHTTPVersion;
  debug << " HEADERS: ";
  std::map<std::string, std::string>::iterator it;
  for (it = tempHeaders.begin(); it != tempHeaders.end(); ++it)
    debug << it->first << " => " << it->second << "\n";
  debug << "BODY: " << tempBody;
  LOG_DEBUG(logger_, debug.str());
}

std::pair<std::string, std::string> *RequestParser::ParseHeader(const std::string line) {
  size_t occurence = line.find(headerDelimiter);
  if (std::string::npos != occurence && occurence > 0) {
    std::string key = line.substr(0, occurence);
    std::string value = line.substr(occurence + headerDelimiter.length());
    return new std::pair<std::string, std::string>(key, value);
  } else {
    return NULL;
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

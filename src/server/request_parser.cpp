#include "server/request_parser.h"

#include "http/request.h"
#include "logger/logger.h"

#include<string>
#include<map>
#include<utility>
#include<sstream>
#include<tuple>

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
      case REQUEST_LINE: {
        std::tuple<http::Request::Method, std::string, std::string> *request_line =
          ParseRequestLine(line);
        if (request_line != NULL) {
          tempHTTPMethod = std::get<0>(*request_line);
          tempURL = std::get<1>(*request_line);
          tempHTTPVersion = std::get<2>(*request_line);
          state_ = HEADERS;
        } else {
          state_ = ERROR;
        }
        break;
      }
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
  LOG_DEBUG(logger_, "HTTP Method: " << tempHTTPMethod);
  LOG_DEBUG(logger_, "URL: " << tempURL);
  LOG_DEBUG(logger_, "HTTP Version: " << tempHTTPVersion);
  std::map<std::string, std::string>::iterator it;
  for (it = tempHeaders.begin(); it != tempHeaders.end(); ++it)
    LOG_DEBUG(logger_, "HEADER: " << it->first << ": " << it->second);
  LOG_DEBUG(logger_, "Body: " << tempBody);
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

std::tuple<http::Request::Method, std::string, std::string> *RequestParser::ParseRequestLine(const std::string line) {
std::smatch match;
  bool found = std::regex_search(line.begin(), line.end(), match, request_line_regex);
  if (found) {
    return new std::tuple<http::Request::Method, std::string, std::string>(StringToMethod(match[1]), match[2], match[3]);
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

http::Request::Method RequestParser::StringToMethod(const std::string input) {
  if (input == "OPTIONS")
    return http::Request::Method::OPTIONS;
  else if (input == "GET")
    return http::Request::Method::GET;
  else if (input == "HEAD")
    return http::Request::Method::HEAD;
  else if (input == "POST")
    return http::Request::Method::POST;
  else if (input == "PUT")
    return http::Request::Method::PUT;
  else if (input == "DELETE")
    return http::Request::Method::DELETE;
  else if (input == "TRACE")
    return http::Request::Method::TRACE;
  else if (input == "CONNECT")
    return http::Request::Method::CONNECT;
}

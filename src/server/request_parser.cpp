#include "server/request_parser.h"

#include "http/request.h"
#include "logger/logger.h"

#include <string>
#include <map>
#include <utility>
#include <sstream>
#include <tuple>
#include <boost/regex.hpp>

using server::RequestParser;

const std::string RequestParser::delimiter_ = { '\r', '\n' };
const std::string RequestParser::header_delimiter_ = { ':', ' ' };
const logger::Logger RequestParser::logger_("server.request_parser");

RequestParser::RequestParser()
  : state_(REQUEST_LINE),
    request_line_regex_(
      "^(OPTIONS|GET|HEAD|POST|PUT|DELETE|TRACE|CONNECT) (.*) HTTP/(\\d\\.\\d)$") {
}

RequestParser::ParseResult RequestParser::Parse(
    const char* buffer, size_t bytes_read, http::Request* request) {
  Reset();
  size_t cursor = 0;
  std::string line;
  while (cursor < bytes_read) {
    switch (state_) {
      case REQUEST_LINE: {
        line = GetLine(buffer + cursor);
        cursor = cursor + line.length() + delimiter_.length();

        std::tuple<http::Request::Method, std::string, std::string> *request_line =
          ParseRequestLine(line);
        if (request_line != nullptr) {
          temp_HTTP_method_ = std::get<0>(*request_line);
          temp_URL_ = std::get<1>(*request_line);
          temp_HTTP_version_ = std::get<2>(*request_line);
          state_ = HEADERS;
        } else {
          state_ = ERROR;
        }
        break;
      }
      case HEADERS:
        line = GetLine(buffer + cursor);
        cursor = cursor + line.length() + delimiter_.length();

        if (line.length() > 0) {
          std::pair<std::string, std::string> *header = ParseHeader(line);
          if (header != nullptr) {
            temp_headers_.insert(*header);
            if (header->first == "Content-Length") {
              content_length_ = std::stoi(header->second);
            }
          } else {
            state_ = ERROR;
          }
        } else {
          if (content_length_ == -1)
            state_ = SUCCESS;
          else
            state_ = BODY;
        }
        break;
      case BODY:
        if (content_length_ == -1) {
          state_ = ERROR;
          break;
        }
        if (content_length_ == 0) {
          state_ = SUCCESS;
          break;
        }
        temp_body_ += buffer[cursor++];
        position_in_content_++;
        if (position_in_content_ >= content_length_) {
          state_ = SUCCESS;
          break;
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
    PopulateRequest(request);
    return RequestParser::GOOD;
  } else {
    return RequestParser::UNKNOWN;
  }
}

void RequestParser::Reset() {
  if (state_ != BODY) {
    temp_body_ = "";
    temp_URL_ = "";
    temp_HTTP_version_ = "";
    temp_HTTP_method_ = http::Request::Method::GET;
    state_ = REQUEST_LINE;
    temp_headers_.clear();
    content_length_ = -1;
    position_in_content_ = 0;
  }
}

void RequestParser::PopulateRequest(http::Request* request) {
  request->content() = temp_body_;
  request->method() = temp_HTTP_method_;
  request->uri() = temp_URL_;
  request->http_version_major() = 1;
  request->http_version_minor() = 1;
  request->headers().clear();
  request->headers().resize(temp_headers_.size());
  int i = 0;
  std::map<std::string, std::string>::iterator it;
  for (it = temp_headers_.begin(); it != temp_headers_.end(); ++it) {
    request->headers()[i].key() = it->first;
    request->headers()[i].value() = it->second;
    i++;
  }
}

void RequestParser::DebugState() {
  LOG_DEBUG(logger_, "HTTP Method: " << temp_HTTP_method_);
  LOG_DEBUG(logger_, "URL: " << temp_URL_);
  LOG_DEBUG(logger_, "HTTP Version: " << temp_HTTP_version_);
  std::map<std::string, std::string>::iterator it;
  for (it = temp_headers_.begin(); it != temp_headers_.end(); ++it)
    LOG_DEBUG(logger_, "HEADER: " << it->first << ": " << it->second);
  LOG_DEBUG(logger_, "Body: " << temp_body_);
}

std::pair<std::string, std::string> *RequestParser::ParseHeader(const std::string &line) {
  size_t occurence = line.find(header_delimiter_);
  if (std::string::npos != occurence && occurence > 0) {
    std::string key = line.substr(0, occurence);
    std::string value = line.substr(occurence + header_delimiter_.length());
    return new std::pair<std::string, std::string>(key, value);
  } else {
    return nullptr;
  }
}

std::tuple<http::Request::Method, std::string, std::string> *RequestParser::ParseRequestLine(
    const std::string &line) {
  boost::smatch match;
  bool found = boost::regex_search(line.begin(), line.end(), match, request_line_regex_);
  if (found) {
    return new std::tuple<http::Request::Method, std::string, std::string>(
      http::Request::StringToMethod(match[1]), match[2], match[3]);
  } else {
    return nullptr;
  }
}

std::string RequestParser::GetLine(const char* buffer) {
  std::string bufferString(buffer);
  size_t occurence = bufferString.find(delimiter_);
  if (std::string::npos == occurence) {
    return bufferString;
  } else {
    return bufferString.substr(0, occurence);
  }
}

#include "http/request.h"

#include <string>
#include <sstream>

#include "logger/logger.h"

using http::Request;
using std::string;
using std::stringstream;

logger::Logger Request::logger_("http.request");

string Request::GetStartLine() const {
  // TODO(?): test
  stringstream start_line;
  start_line << MethodString()
    << " "
    << uri_
    << " "
    << "HTTP/"
    << http_version_major_
    << "."
    << http_version_minor_
    << "\r\n";
  return start_line.str();
}

std::string Request::MethodString() const {
  switch (method_) {
  case OPTIONS:
    return "OPTIONS";
  case GET:
    return "GET";
  case HEAD:
    return "HEAD";
  case POST:
    return "POST";
  case PUT:
    return "PUT";
  case DELETE:
    return "DELETE";
  case TRACE:
    return "TRACE";
  case CONNECT:
    return "CONNECT";
  default:
    return "";
  }
}

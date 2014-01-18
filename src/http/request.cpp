#include "http/request.h"

#include <string>
#include <sstream>

#include "logger/logger.h"

#include<assert.h>

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

http::Request::Method Request::StringToMethod(const std::string &input) {
  if (input == "OPTIONS")
    return Method::OPTIONS;
  else if (input == "GET")
    return Method::GET;
  else if (input == "HEAD")
    return Method::HEAD;
  else if (input == "POST")
    return Method::POST;
  else if (input == "PUT")
    return Method::PUT;
  else if (input == "DELETE")
    return Method::DELETE;
  else if (input == "TRACE")
    return Method::TRACE;
  else if (input == "CONNECT")
    return Method::CONNECT;
  else
    assert(false);
}

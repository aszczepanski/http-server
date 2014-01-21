#include "http/response.h"

#include <string>
#include <sstream>

#include "logger/logger.h"

using std::string;
using std::stringstream;
using http::Response;

logger::Logger Response::logger_("http.response");

Response::Response() {
  http_version_major_ = 1;
  http_version_minor_ = 1;  // TODO(?): change it ?
}

void Response::Clear() {
  http_version_major_ = 1;
  http_version_minor_ = 1;
  headers_.clear();
  content_.clear();
  status_ = Response::NO_CONTENT;
}

string Response::GetStartLine() const {
  stringstream start_line;
  start_line << "HTTP/"
    << http_version_major_
    << "."
    << http_version_minor_
    << " "
    << StatusString();
  return start_line.str();
}

Response Response::StockResponse(Status status) {
  Response response;
  response.status() = status;
  response.content() = response.ContentString();
  response.headers().resize(2);
  response.headers()[0].key() = "Content-Length";
  response.headers()[0].value() = std::to_string(response.content().size());
  response.headers()[1].key() = "Content-Type";
  response.headers()[1].value() = "text/html";
  return response;
}

std::string Response::StatusString() const {
  switch (status_) {
  case OK:
    return "200 OK\r\n";
  case CREATED:
    return "201 Created\r\n";
  case ACCEPTED:
    return "202 Accepted\r\n";
  case NO_CONTENT:
    return "204 No Content\r\n";
  case MULTIPLE_CHOICES:
    return "300 Multiple Choices\r\n";
  case MOVED_PERMANENTLY:
    return "301 Moved Permanently\r\n";
  case MOVED_TEMPORARILY:
    return "302 Moved Temporarily\r\n";
  case NOT_MODIFIED:
    return "304 Not Modified\r\n";
  case BAD_REQUEST:
    return "400 Bad Request\r\n";
  case UNAUTHORIZED:
    return "401 Unauthorized\r\n";
  case FORBIDDEN:
    return "403 Forbidden\r\n";
  case NOT_FOUND:
    return "404 Not Found\r\n";
  case INTERNAL_SERVER_ERROR:
    return "500 Internal Server Error\r\n";
  case NOT_IMPLEMENTED:
    return "501 Not Implemented\r\n";
  case BAD_GATEWAY:
    return "502 Bad Gateway\r\n";
  case SERVICE_UNAVAILABLE:
    return "503 Service Unavailable\r\n";
  default:
    return "500 Internal Server Error\r\n";
  }
}

// TODO(adam): move it to file
std::string Response::ContentString() const {
  switch (status_) {
    case OK:
      return "";
    case CREATED:
      return "<html>"
        "<head><title>Created</title></head>"
        "<body><h1>201 Created</h1></body>"
        "</html>";
    case ACCEPTED:
      return "<html>"
        "<head><title>Accepted</title></head>"
        "<body><h1>202 Accepted</h1></body>"
        "</html>";
    case NO_CONTENT:
      return "<html>"
        "<head><title>No Content</title></head>"
        "<body><h1>204 No Content</h1></body>"
        "</html>";
    case MULTIPLE_CHOICES:
      return "<html>"
        "<head><title>Multiple Choices</title></head>"
        "<body><h1>300 Multiple Choices</h1></body>"
        "</html>";
    case MOVED_PERMANENTLY:
      return "<html>"
        "<head><title>Moved Permanently</title></head>"
        "<body><h1>301 Moved Permanently</h1></body>"
        "</html>";
    case MOVED_TEMPORARILY:
      return "<html>"
        "<head><title>Moved Temporarily</title></head>"
        "<body><h1>302 Moved Temporarily</h1></body>"
        "</html>";
    case NOT_MODIFIED:
      return "<html>"
        "<head><title>Not Modified</title></head>"
        "<body><h1>304 Not Modified</h1></body>"
        "</html>";
    case BAD_REQUEST:
      return "<html>"
        "<head><title>Bad Request</title></head>"
        "<body><h1>400 Bad Request</h1></body>"
        "</html>";
    case UNAUTHORIZED:
      return "<html>"
        "<head><title>Unauthorized</title></head>"
        "<body><h1>401 Unauthorized</h1></body>"
        "</html>";
    case FORBIDDEN:
      return "<html>"
        "<head><title>Forbidden</title></head>"
        "<body><h1>403 Forbidden</h1></body>"
        "</html>";
    case NOT_FOUND:
      return "<html>"
        "<head><title>404 Not Found</title></head>"
        "<body><h1>404 Not Found</h1></body>"
        "</html>";
    case INTERNAL_SERVER_ERROR:
      return "<html>"
        "<head><title>Internal Server Error</title></head>"
        "<body><h1>500 Internal Server Error</h1></body>"
        "</html>";
    case NOT_IMPLEMENTED:
      return "<html>"
        "<head><title>Not Implemented</title></head>"
        "<body><h1>501 Not Implemented</h1></body>"
        "</html>";
    case BAD_GATEWAY:
      return "<html>"
        "<head><title>Bad Gateway</title></head>"
        "<body><h1>502 Bad Gateway</h1></body>"
        "</html>";
    case SERVICE_UNAVAILABLE:
      return "<html>"
        "<head><title>Service Unavailable</title></head>"
        "<body><h1>503 Service Unavailable</h1></body>"
        "</html>";
    default:
      return "<html>"
        "<head><title>Internal Server Error</title></head>"
        "<body><h1>500 Internal Server Error</h1></body>"
        "</html>";
  }
}


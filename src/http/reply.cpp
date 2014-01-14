#include "http/reply.h"

#include <string>

#include "logger/logger.h"

using std::string;
using http::Reply;

logger::Logger Reply::logger_("http.reply");

static const string separator = { ':', ' ' };
static const string crlf = { '\r', '\n' };

Reply Reply::StockReply(Status status) {
  Reply reply;
  reply.status_ = status;
  reply.content_ = reply.ContentString();
  reply.headers_.resize(2);
  reply.headers_[0].key() = "Content-Length";
  reply.headers_[0].value() = std::to_string(reply.content_.size());
  reply.headers_[1].key() = "Content-Type";
  reply.headers_[1].value() = "text/html";
  return reply;
}

std::string Reply::StatusString() const {
  switch (status_) {
  case ok:
    return "HTTP/1.0 200 OK\r\n";
  case created:
    return "HTTP/1.0 201 Created\r\n";
  case accepted:
    return "HTTP/1.0 202 Accepted\r\n";
  case no_content:
    return "HTTP/1.0 204 No Content\r\n";
  case multiple_choices:
    return "HTTP/1.0 300 Multiple Choices\r\n";
  case moved_permanently:
    return "HTTP/1.0 301 Moved Permanently\r\n";
  case moved_temporarily:
    return "HTTP/1.0 302 Moved Temporarily\r\n";
  case not_modified:
    return "HTTP/1.0 304 Not Modified\r\n";
  case bad_request:
    return "HTTP/1.0 400 Bad Request\r\n";
  case unauthorized:
    return "HTTP/1.0 401 Unauthorized\r\n";
  case forbidden:
    return "HTTP/1.0 403 Forbidden\r\n";
  case not_found:
    return "HTTP/1.0 404 Not Found\r\n";
  case internal_server_error:
    return "HTTP/1.0 500 Internal Server Error\r\n";
  case not_implemented:
    return "HTTP/1.0 501 Not Implemented\r\n";
  case bad_gateway:
    return "HTTP/1.0 502 Bad Gateway\r\n";
  case service_unavailable:
    return "HTTP/1.0 503 Service Unavailable\r\n";
  default:
    return "HTTP/1.0 500 Internal Server Error\r\n";
  }
}

// TODO(adam): move it to file
std::string Reply::ContentString() const {
  switch (status_) {
    case ok:
      return "";
    case created:
      return "<html>"
        "<head><title>Created</title></head>"
        "<body><h1>201 Created</h1></body>"
        "</html>";
    case accepted:
      return "<html>"
        "<head><title>Accepted</title></head>"
        "<body><h1>202 Accepted</h1></body>"
        "</html>";
    case no_content:
      return "<html>"
        "<head><title>No Content</title></head>"
        "<body><h1>204 No Content</h1></body>"
        "</html>";
    case multiple_choices:
      return "<html>"
        "<head><title>Multiple Choices</title></head>"
        "<body><h1>300 Multiple Choices</h1></body>"
        "</html>";
    case moved_permanently:
      return "<html>"
        "<head><title>Moved Permanently</title></head>"
        "<body><h1>301 Moved Permanently</h1></body>"
        "</html>";
    case moved_temporarily:
      return "<html>"
        "<head><title>Moved Temporarily</title></head>"
        "<body><h1>302 Moved Temporarily</h1></body>"
        "</html>";
    case not_modified:
      return "<html>"
        "<head><title>Not Modified</title></head>"
        "<body><h1>304 Not Modified</h1></body>"
        "</html>";
    case bad_request:
      return "<html>"
        "<head><title>Bad Request</title></head>"
        "<body><h1>400 Bad Request</h1></body>"
        "</html>";
    case unauthorized:
      return "<html>"
        "<head><title>Unauthorized</title></head>"
        "<body><h1>401 Unauthorized</h1></body>"
        "</html>";
    case forbidden:
      return "<html>"
        "<head><title>Forbidden</title></head>"
        "<body><h1>403 Forbidden</h1></body>"
        "</html>";
    case not_found:
      return "<html>"
        "<head><title>404 Not Found</title></head>"
        "<body><h1>404 Not Found</h1></body>"
        "</html>";
    case internal_server_error:
      return "<html>"
        "<head><title>Internal Server Error</title></head>"
        "<body><h1>500 Internal Server Error</h1></body>"
        "</html>";
    case not_implemented:
      return "<html>"
        "<head><title>Not Implemented</title></head>"
        "<body><h1>501 Not Implemented</h1></body>"
        "</html>";
    case bad_gateway:
      return "<html>"
        "<head><title>Bad Gateway</title></head>"
        "<body><h1>502 Bad Gateway</h1></body>"
        "</html>";
    case service_unavailable:
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

std::string Reply::ToString() const {
  std::string result;

  result += StatusString();

  for (auto h : headers_) {
    result += h.key();
    result += separator;
    result += h.value();
    result += crlf;
  }

  result += crlf;
  result += content_;

  LOG_DEBUG(logger_, "Reply ToString: \n" << result)

  return result;
}

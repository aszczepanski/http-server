#include "http/reply.h"

#include <string>

#include "logger/logger.h"

using std::string;
using http::Reply;

logger::Logger Reply::logger_("http.reply");

namespace status_strings {

static const string ok =
"HTTP/1.0 200 OK\r\n";
static const string created =
"HTTP/1.0 201 Created\r\n";
static const string accepted =
"HTTP/1.0 202 Accepted\r\n";
static const string no_content =
"HTTP/1.0 204 No Content\r\n";
static const string multiple_choices =
"HTTP/1.0 300 Multiple Choices\r\n";
static const string moved_permanently =
"HTTP/1.0 301 Moved Permanently\r\n";
static const string moved_temporarily =
"HTTP/1.0 302 Moved Temporarily\r\n";
static const string not_modified =
"HTTP/1.0 304 Not Modified\r\n";
static const string bad_request =
"HTTP/1.0 400 Bad Request\r\n";
static const string unauthorized =
"HTTP/1.0 401 Unauthorized\r\n";
static const string forbidden =
"HTTP/1.0 403 Forbidden\r\n";
static const string not_found =
"HTTP/1.0 404 Not Found\r\n";
static const string internal_server_error =
"HTTP/1.0 500 Internal Server Error\r\n";
static const string not_implemented =
"HTTP/1.0 501 Not Implemented\r\n";
static const string bad_gateway =
"HTTP/1.0 502 Bad Gateway\r\n";
static const string service_unavailable =
"HTTP/1.0 503 Service Unavailable\r\n";

}  // namespace status_strings

static const string separator = { ':', ' ' };
static const string crlf = { '\r', '\n' };

Reply Reply::StockReply(StatusType status) {
  Reply reply;
  reply.status = status;
  reply.content = "";  // TODO(adam): content related to status
  reply.headers.resize(2);
  reply.headers[0].key = "Content-Length";
  reply.headers[0].value = std::to_string(reply.content.size());
  reply.headers[1].key = "Content-Type";
  reply.headers[1].value = "text/html";
  return reply;
}

std::string Reply::StatusString() const {
  switch (status) {
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
  }
}

std::string Reply::ToString() const {
  std::string result;

  result += StatusString();

  for (auto h : headers) {
    result += h.key;
    result += separator;
    result += h.value;
    result += crlf;
  }

  result += crlf;
  result += content;

  LOG_DEBUG(logger_, "Reply ToString: \n" << result)

  return result;
}

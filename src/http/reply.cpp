#include "http/reply.h"
#include <string>

using std::string;
using http::Reply;

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

static const char separator[] = { ':', ' ' };
static const char crlf[] = { '\r', '\n' };

Reply Reply::StockReply(kStatusType status) {
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

#include "server/request_handler_trace.h"

#include "http/request.h"
#include "http/response.h"

using http::Request;
using http::Response;

namespace server {

logger::Logger RequestHandlerTRACE::logger_("server.request_handler_post");

void RequestHandlerTRACE::HandleRequest(
    const Request& request, Response* response) const {
  response->status() = Response::OK;

  response->content() = request.ToString();

  response->headers().resize(2);
  response->headers()[0].key() = "Content-Length";
  response->headers()[0].value() = std::to_string(response->content().size());
  response->headers()[1].key() = "Content-Type";
  response->headers()[1].value() = "text/html";
}

}  // namespace server

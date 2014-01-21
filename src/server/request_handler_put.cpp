#include "server/request_handler_put.h"

#include "http/response.h"

using http::Response;

namespace server {

logger::Logger RequestHandlerPUT::logger_("server.request_handler_put");

void RequestHandlerPUT::HandleRequest(
    const http::Request&, Response* response) const {
  LOG_DEBUG(logger_, "Creating stock response: UNAUTHORIZED")
  *response = Response::StockResponse(Response::UNAUTHORIZED);
}

}  // namespace server

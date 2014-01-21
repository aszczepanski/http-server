#include "server/request_handler_delete.h"

#include "http/response.h"

using http::Response;

namespace server {

logger::Logger RequestHandlerDELETE::logger_("server.request_handler_delete");

void RequestHandlerDELETE::HandleRequest(
    const http::Request&, Response* response) const {
  LOG_DEBUG(logger_, "Creating stock response: UNAUTHORIZED")
  *response = Response::StockResponse(Response::UNAUTHORIZED);
}

}  // namespace server

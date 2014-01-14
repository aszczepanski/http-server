#include "server/request_handler_get.h"

#include "logger/logger.h"
#include "http/request.h"
#include "http/response.h"
#include "http/header.h"

using server::RequestHandlerGET;
using http::Request;
using http::Response;
using http::Header;

logger::Logger RequestHandlerGET::logger_("server.request_handler_get");

void RequestHandlerGET::HandleRequest(
    const http::Request& request, http::Response* response) const {
  *response = Response::StockResponse(Response::NOT_IMPLEMENTED);
}

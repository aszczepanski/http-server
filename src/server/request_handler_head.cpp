#include "server/request_handler_head.h"

#include "logger/logger.h"
#include "http/request.h"
#include "http/response.h"

using server::RequestHandlerHEAD;
using server::RequestHandlerGET;
using http::Request;
using http::Response;

logger::Logger RequestHandlerHEAD::logger_("server.request_handler_head");

void RequestHandlerHEAD::HandleRequest(
    const http::Request& request, http::Response* response) const {
  RequestHandlerGET::HandleRequest(request, response);
  response->content() = "";
}

#include "server/request_handler.h"

#include "http/request.h"
#include "http/response.h"
#include "logger/logger.h"
#include "settings/settings.h"

#include "server/request_handler_base.h"
#include "server/request_handler_get.h"

using server::RequestHandler;
using http::Request;
using http::Response;

const logger::Logger RequestHandler::logger_("server.request_handler");

RequestHandler::RequestHandler()
  : request_handler_get_() {
}

RequestHandler::~RequestHandler() {
}

void RequestHandler::HandleRequest(const Request& request, Response* response) const {
  switch (request.method()) {
    case Request::GET:
      request_handler_get_.HandleRequest(request, response);
      break;
    default:
      RequestHandlerBase::HandleRequest(request, response);
  }
}


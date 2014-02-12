#include "server/request_handler.h"

#include "http/request.h"
#include "http/response.h"
#include "logger/logger.h"
#include "settings/settings.h"

#include "server/request_handler_base.h"
#include "server/request_handler_delete.h"
#include "server/request_handler_get.h"
#include "server/request_handler_post.h"
#include "server/request_handler_put.h"
#include "server/request_handler_trace.h"

using server::RequestHandler;
using http::Request;
using http::Response;

const logger::Logger RequestHandler::logger_("server.request_handler");

RequestHandler::RequestHandler()
  : request_handler_delete_(),
    request_handler_get_(),
    request_handler_post_(),
    request_handler_put_() {
}

RequestHandler::~RequestHandler() {
}

void RequestHandler::HandleRequest(const Request& request, Response* response) const {
  response->Clear();
  switch (request.method()) {
    case Request::DELETE:
      request_handler_delete_.HandleRequest(request, response);
      break;
    case Request::GET:
      request_handler_get_.HandleRequest(request, response);
      break;
    case Request::POST:
      request_handler_post_.HandleRequest(request, response);
      break;
    case Request::PUT:
      request_handler_put_.HandleRequest(request, response);
      break;
    case Request::TRACE:
      request_handler_trace_.HandleRequest(request, response);
    default:
      RequestHandlerBase::HandleRequest(request, response);
  }
}


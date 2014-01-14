#include "server/request_handler.h"

#include <iostream>
#include <string>

#include "http/request.h"
#include "http/reply.h"
#include "logger/logger.h"
#include "settings/settings.h"

#include "server/request_handler_get.h"

using server::RequestHandler;
using http::Request;
using http::Reply;

using std::cout;
using std::endl;
using std::string;

const logger::Logger RequestHandler::logger_("server.request_handler");

RequestHandler::RequestHandler()
  : request_handler_get_() {
}

RequestHandler::~RequestHandler() {
}

void RequestHandler::HandleRequest(const Request& request, Reply* reply) const {
  switch (request.method()) {
    case Request::GET:
      request_handler_get_.HandleRequest(request, reply);
      break;
    default:
      RequestHandlerBase::HandleRequest(request, reply);
  }
}


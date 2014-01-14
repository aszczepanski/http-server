#include "server/request_handler_get.h"

#include "logger/logger.h"
#include "http/request.h"
#include "http/reply.h"
#include "http/header.h"

using server::RequestHandlerGET;
using http::Request;
using http::Reply;
using http::Header;

logger::Logger RequestHandlerGET::logger_("server.request_handler_get");

void RequestHandlerGET::HandleRequest(const http::Request& request, http::Reply* reply) const {
/*
  string request_path;
  if (!UriToPath(request.uri(), &request_path)) {
    *reply = Reply::StockReply(Reply::BAD_REQUEST);
  }
  *reply = Reply::StockReply(Reply::OK);  // TODO(adam): test only
*/
  *reply = Reply::StockReply(Reply::NOT_IMPLEMENTED);
}

#include "server/request_handler.h"

#include <iostream>
#include <string>

#include "http/request.h"
#include "http/reply.h"
#include "logger/logger.h"

using server::RequestHandler;
using http::Request;
using http::Reply;

using std::cout;
using std::endl;
using std::string;

const logger::Logger RequestHandler::logger_("server.request_handler");

RequestHandler::RequestHandler(const libconfig::Config& config) {
  config.lookupValue("root_directory", root_directory_);
  LOG_INFO(logger_, "Root directory: " << root_directory_)
}

void RequestHandler::HandleRequest(const Request& request, Reply* reply) const {
  string request_path;
  if (!UriToPath(request.uri(), &request_path)) {
    *reply = Reply::StockReply(Reply::ok);
  }
  *reply = Reply::StockReply(Reply::ok);  // TODO(adam): test only
}

bool RequestHandler::UriToPath(const string& uri, string* path) const {
  path->clear();
  return true;
}

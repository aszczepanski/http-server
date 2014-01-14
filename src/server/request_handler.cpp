#include "server/request_handler.h"

#include <iostream>
#include <string>

#include "http/request.h"
#include "http/reply.h"
#include "logger/logger.h"
#include "settings/settings.h"

using server::RequestHandler;
using http::Request;
using http::Reply;

using std::cout;
using std::endl;
using std::string;

const logger::Logger RequestHandler::logger_("server.request_handler");

RequestHandler::RequestHandler() {
  settings::Settings& settings = settings::Settings::getSettings();
  root_directory_ = settings.GetValue<string>("root_directory");
  LOG_INFO(logger_, "Root directory: " << root_directory_)
}

void RequestHandler::HandleRequest(const Request& request, Reply* reply) const {
  string request_path;
  if (!UriToPath(request.uri(), &request_path)) {
    *reply = Reply::StockReply(Reply::BAD_REQUEST);
  }
  *reply = Reply::StockReply(Reply::OK);  // TODO(adam): test only
}

bool RequestHandler::UriToPath(const string& uri, string* path) const {
  path->clear();
  return true;
}

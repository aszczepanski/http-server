#include "server/request_handler.h"
#include "http/request.h"
#include "http/reply.h"

#include <iostream>

using server::RequestHandler;
using http::Request;
using http::Reply;

using std::cout;
using std::endl;

RequestHandler::RequestHandler(const libconfig::Config& config) {
  config.lookupValue("root_directory", root_directory_);
  cout << "root_directory: " << root_directory_ << endl;
}

void RequestHandler::HandleRequest(const Request& request, Reply* reply) {
  *reply = Reply::StockReply(Reply::ok);  // TODO(adam): test only
}

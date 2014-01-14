#include "server/request_handler_base.h"

#include <string>

#include "settings/settings.h"
#include "logger/logger.h"
#include "http/reply.h"

using server::RequestHandlerBase;
using std::string;
using http::Reply;

logger::Logger RequestHandlerBase::logger_("server.request_handler_base");

RequestHandlerBase::RequestHandlerBase() {
  settings::Settings& settings = settings::Settings::getSettings();
  root_directory_ = settings.GetValue<string>("root_directory");
  LOG_INFO(logger_, "Root directory: " << root_directory_)
}

RequestHandlerBase::~RequestHandlerBase() {
}

void RequestHandlerBase::HandleRequest(const http::Request& request, http::Reply* reply) const {
  LOG_DEBUG(logger_, "Creating stock reply: NOT IMPLEMENTED")
  *reply = Reply::StockReply(Reply::NOT_IMPLEMENTED);
}

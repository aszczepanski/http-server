#include "server/request_handler_base.h"

#include <string>

#include "settings/settings.h"
#include "logger/logger.h"
#include "http/response.h"

using server::RequestHandlerBase;
using std::string;
using http::Response;

logger::Logger RequestHandlerBase::logger_("server.request_handler_base");

RequestHandlerBase::RequestHandlerBase() {
  settings::Settings& settings = settings::Settings::getSettings();
  root_directory_ = settings.GetValue<string>("root_directory");
  LOG_INFO(logger_, "Root directory: " << root_directory_)
}

RequestHandlerBase::~RequestHandlerBase() {
}

void RequestHandlerBase::HandleRequest(
    const http::Request&, http::Response* response) const {
  LOG_DEBUG(logger_, "Creating stock response: NOT IMPLEMENTED")
  *response = Response::StockResponse(Response::NOT_IMPLEMENTED);
}

std::string RequestHandlerBase::GetExtension(
    const std::string& full_path) const {
  string extension;
  std::size_t last_dot_pos = full_path.find_last_of(".");
  if (last_dot_pos != string::npos) {
    extension = full_path.substr(last_dot_pos + 1);
  }
  return extension;
}

bool RequestHandlerBase::DecodeURL(
    const std::string& url, std::string* path,
    std::string* query, std::string* fragment) const {
  std::string* cur_string = path;

  path->clear();
  query->clear();
  fragment->clear();

  for (std::size_t i = 0; i < url.size(); ++i) {
    if (url[i] == '%') {
      if (i + 3 <= url.size()) {
        int value = 0;
        std::istringstream is(url.substr(i + 1, 2));
        if (is >> std::hex >> value) {
          *cur_string += static_cast<char>(value);
          i += 2;
        } else {
          return false;
        }
      } else {
        return false;
      }
    } else if (url[i] == '+') {
      *cur_string += ' ';
    } else if (url[i] == '?') {
      cur_string = query;
    } else if (url[i] == '#') {
      cur_string = fragment;
    } else {
      *cur_string += url[i];
    }
  }
  return true;
}


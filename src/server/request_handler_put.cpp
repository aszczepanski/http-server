#include "server/request_handler_put.h"

#include <string>
#include <cstring>
#include <fstream>
#include <boost/filesystem.hpp>

#include "http/response.h"
#include "http/request.h"

using http::Response;
using std::string;

namespace server {

logger::Logger RequestHandlerPUT::logger_("server.request_handler_put");

void RequestHandlerPUT::WriteFile(
    const string& full_path, const char* content, Response* response) const {
  // TODO(?): tests

  bool new_file = false;

  boost::filesystem::path path(full_path);

  if (!boost::filesystem::exists(path)) {
    new_file = true;
    LOG_DEBUG(logger_, "Creating directory")

    if (!boost::filesystem::exists(path.parent_path())) {
      if (boost::filesystem::create_directory(path.parent_path())) {
        LOG_INFO(logger_, path.parent_path() << " directory created")
      }
    }
  }

  std::ofstream os(full_path, std::ios::out | std::ios::binary);
  if (!os) {
    *response = Response::StockResponse(Response::INTERNAL_SERVER_ERROR);
    return;
  }

  os.write(content, strlen(content));

  os.close();

  if (new_file) {
    *response = Response::StockResponse(Response::CREATED);
  } else {
    *response = Response::StockResponse(Response::OK);
  }
}

void RequestHandlerPUT::HandleRequest(
    const http::Request& request, Response* response) const {
  string path;
  string rest;
  string fragment;

  if (!DecodeURL(request.uri(), &path, &rest, &fragment)) {
    *response = Response::StockResponse(Response::BAD_REQUEST);
    return;
  }

  LOG_DEBUG(logger_, "path: " << path)
  LOG_DEBUG(logger_, "rest: " << rest)
  LOG_DEBUG(logger_, "fragment: " << fragment)

  string full_path = root_directory_ + path;

  LOG_DEBUG(logger_, full_path)

  WriteFile(full_path, request.content().c_str(), response);
}

}  // namespace server

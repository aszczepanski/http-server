#include "server/request_handler_delete.h"

#include <boost/filesystem.hpp>
#include <string>

#include "http/response.h"
#include "http/request.h"
#include "logger/logger.h"

using http::Response;
using std::string;

namespace server {

logger::Logger RequestHandlerDELETE::logger_("server.request_handler_delete");

void RequestHandlerDELETE::DeleteFile(const string& full_path,
    Response* response) const {
  // TODO(?): tests

  boost::filesystem::path path(full_path);

  if (!boost::filesystem::remove(path)) {
    *response = Response::StockResponse(Response::NOT_FOUND);
  } else {
    *response = Response::StockResponse(Response::ACCEPTED);
  }
}

void RequestHandlerDELETE::HandleRequest(
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

  DeleteFile(full_path, response);
}

}  // namespace server

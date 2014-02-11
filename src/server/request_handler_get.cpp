#include "server/request_handler_get.h"

#include <string>
#include <cstdio>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <sstream>

#include "logger/logger.h"
#include "http/request.h"
#include "http/response.h"
#include "http/header.h"
#include "http/mime.h"

using server::RequestHandlerGET;
using http::Request;
using http::Response;
using http::Header;
using std::string;
using std::vector;

logger::Logger RequestHandlerGET::logger_("server.request_handler_get");

static std::string exec(const char* cmd) {
  FILE* pipe = popen(cmd, "r");
  if (!pipe) return "ERROR";  // TODO(adam): exception
  char buffer[128];
  std::string result = "";
  while (!feof(pipe)) {
    if (fgets(buffer, 128, pipe) != NULL)
      result += buffer;
  }
  pclose(pipe);
  return result;
}

void RequestHandlerGET::CreateNormalResponse(
    const std::string& full_path, http::Response* response) const {
  std::ifstream is(full_path, std::ios::in | std::ios::binary);
  if (!is) {
    *response = Response::StockResponse(Response::NOT_FOUND);
    return;
  }

  response->status() = Response::OK;
  char buf[512];
  while (is.read(buf, sizeof(buf)).gcount() > 0) {
    response->content().append(buf, is.gcount());
  }

  std::string extension = GetExtension(full_path);

  response->headers().resize(2);
  response->headers()[0].key() = "Content-Length";
  response->headers()[0].value() = std::to_string(response->content().size());
  response->headers()[1].key() = "Content-Type";
  response->headers()[1].value() = http::Mime::GetInstance().GetType(extension);
}

void RequestHandlerGET::CreatePHPResponse(
    const std::string& full_path, http::Response* response) const {
  string php_cgi_query = "php5-cgi " + full_path;
  response->content() = exec(php_cgi_query.c_str());

  response->status() = Response::OK;

  response->headers().resize(2);
  response->headers()[0].key() = "Content-Length";
  response->headers()[0].value() = std::to_string(response->content().size());
  response->headers()[1].key() = "Content-Type";
  response->headers()[1].value() = "text/html";
}

void RequestHandlerGET::CreateResponse(
    const std::string& full_path, http::Response* response) const {
  string extension = GetExtension(full_path);
  LOG_DEBUG(logger_, "extension: " << extension)
  if (extension == "php") {
    CreatePHPResponse(full_path, response);
  } else {
    CreateNormalResponse(full_path, response);
  }
}

void RequestHandlerGET::HandleRequest(
    const http::Request& request, http::Response* response) const {
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

  CreateResponse(full_path, response);
}

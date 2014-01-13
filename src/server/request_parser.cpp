#include "server/request_parser.h"

#include "http/request.h"
#include "logger/logger.h"

using server::RequestParser;

const logger::Logger RequestParser::logger_("server.request_parser");

RequestParser::ParseResult RequestParser::Parse(
    const char* buffer, size_t bytes_read, http::Request* request) {
  // TODO(pewniak): parse
  return RequestParser::kBad;
}

#ifndef SRC_SERVER_REQUEST_PARSER_H_
#define SRC_SERVER_REQUEST_PARSER_H_

#include "http/request.h"
#include "logger/logger.h"

#include<string>
#include<vector>

namespace server {

class RequestParser {
 public:
  enum ParseResult {
    GOOD,
    BAD,
    UNKNOWN
  };

  /*
   * returns:
   * GOOD - valid request
   * BAD - invalid request
   * UNKNOWN - requires more data
   */
  ParseResult Parse(
    const char* buffer, size_t bytes_read, http::Request* request);

 private:
  static const logger::Logger logger_;

  enum ParserState {
    REQUEST_LINE,
    HEADERS,
    BODY,
    ERROR,
    SUCCESS
  };

  ParserState state_ = REQUEST_LINE;

  const std::string delimiter = { '\r', '\n' };

  std::string GetLine(const char* buffer);
  void Reset();

  std::string tempBody;
  std::vector<http::Header> tempHeaders;
};

}  // namespace server

#endif  // SRC_SERVER_REQUEST_PARSER_H_

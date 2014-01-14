#ifndef SRC_SERVER_REQUEST_PARSER_H_
#define SRC_SERVER_REQUEST_PARSER_H_

#include "http/request.h"
#include "logger/logger.h"

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
    const char* buffer, size_t bytes_read, http::Request* request) const;

 private:
  static const logger::Logger logger_;
};

}  // namespace server

#endif  // SRC_SERVER_REQUEST_PARSER_H_

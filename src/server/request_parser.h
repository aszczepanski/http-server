#ifndef SRC_SERVER_REQUEST_PARSER_H_
#define SRC_SERVER_REQUEST_PARSER_H_

#include "http/request.h"
#include "logger/logger.h"

namespace server {

class RequestParser {
 public:
  enum ParseResult {
    kGood,
    kBad,
    kUnknown
  };

  /*
   * returns:
   * kGood - valid request
   * kBad - invalid request
   * kUnknown - requires more data
   */
  ParseResult Parse(
    const char* buffer, size_t bytes_read, http::Request* request);

 private:
  static const logger::Logger logger_;
};

}  // namespace server

#endif  // SRC_SERVER_REQUEST_PARSER_H_

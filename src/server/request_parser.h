#ifndef SRC_SERVER_REQUEST_PARSER_H_
#define SRC_SERVER_REQUEST_PARSER_H_

#include "http/request.h"
#include "logger/logger.h"

#include<string>
#include<vector>
#include<map>
#include<utility>
#include<regex>

namespace server {

class RequestParser {
 public:
  enum ParseResult {
    GOOD,
    BAD,
    UNKNOWN,
    END_CONNECTION
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
  const std::string headerDelimiter = { ':', ' ' };
  const std::regex request_line_regex = std::regex("^(OPTIONS|GET|HEAD|POST|PUT|DELETE|TRACE|CONNECT) (.*) HTTP/(\\d\\.\\d)$");

  std::string GetLine(const char* buffer);
  std::pair<std::string, std::string> *ParseHeader(const std::string &line);
  std::tuple<http::Request::Method, std::string, std::string> *ParseRequestLine(const std::string &line);
  void DebugState();
  void Reset();

  std::string tempURL;
  std::string tempHTTPVersion;
  http::Request::Method tempHTTPMethod;
  std::string tempBody;
  std::map<std::string, std::string> tempHeaders;
};

}  // namespace server

#endif  // SRC_SERVER_REQUEST_PARSER_H_

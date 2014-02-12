#ifndef SRC_SERVER_REQUEST_PARSER_H_
#define SRC_SERVER_REQUEST_PARSER_H_

#include "http/request.h"
#include "logger/logger.h"

#include <string>
#include <vector>
#include <map>
#include <utility>
#include <boost/regex.hpp>

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

  RequestParser();

 private:
  static const logger::Logger logger_;

  enum ParserState {
    REQUEST_LINE,
    HEADERS,
    BODY,
    ERROR,
    SUCCESS
  };

  ParserState state_;

  static const std::string delimiter_;
  static const std::string header_delimiter_;
  const boost::regex request_line_regex_;

  std::string GetLine(const char* buffer);
  std::pair<std::string, std::string> *ParseHeader(const std::string &line);
  std::tuple<http::Request::Method, std::string, std::string> *ParseRequestLine(
    const std::string &line);
  void PopulateRequest(http::Request *request);
  void DebugState();
  void Reset();

  std::string temp_URL_;
  std::string temp_HTTP_version_;
  http::Request::Method temp_HTTP_method_;
  std::string temp_body_;
  std::map<std::string, std::string> temp_headers_;
  int content_length_;
  int position_in_content_;
};

}  // namespace server

#endif  // SRC_SERVER_REQUEST_PARSER_H_

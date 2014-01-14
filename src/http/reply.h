#ifndef SRC_HTTP_REPLY_H_
#define SRC_HTTP_REPLY_H_

#include <vector>
#include <string>
#include "http/header.h"
#include "logger/logger.h"

namespace http {

class Reply {
 public:
  enum Status {
    ok = 200,
    created = 201,
    accepted = 202,
    no_content = 204,
    multiple_choices = 300,
    moved_permanently = 301,
    moved_temporarily = 302,
    not_modified = 304,
    bad_request = 400,
    unauthorized = 401,
    forbidden = 403,
    not_found = 404,
    internal_server_error = 500,
    not_implemented = 501,
    bad_gateway = 502,
    service_unavailable = 503
  };

  std::vector<Header>& headers() { return headers_; }
  const std::vector<Header>& headers() const { return headers_; }

  std::string& content() { return content_; }
  const std::string& content() const { return content_; }

  Status& status() { return status_; }
  const Status& status() const { return status_; }

  std::string ToString() const;

  static Reply StockReply(Status status);

 private:
  std::string StatusString() const;
  std::string ContentString() const;

  std::vector<Header> headers_;
  std::string content_;
  Status status_;

  static logger::Logger logger_;
};

}  // namespace http

#endif  // SRC_HTTP_REPLY_H_

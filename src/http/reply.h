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
    OK = 200,
    CREATED = 201,
    ACCEPTED = 202,
    NO_CONTENT = 204,
    MULTIPLE_CHOICES = 300,
    MOVED_PERMANENTLY = 301,
    MOVED_TEMPORARILY = 302,
    NOT_MODIFIED = 304,
    BAD_REQUEST = 400,
    UNAUTHORIZED = 401,
    FORBIDDEN = 403,
    NOT_FOUND = 404,
    INTERNAL_SERVER_ERROR = 500,
    NOT_IMPLEMENTED = 501,
    BAD_GATEWAY = 502,
    SERVICE_UNAVAILABLE = 503
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

#ifndef SRC_HTTP_RESPONSE_H_
#define SRC_HTTP_RESPONSE_H_

#include "http/message.h"

#include <vector>
#include <string>

#include "http/header.h"
#include "logger/logger.h"

namespace http {

class Response : public Message {
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

  Status& status() { return status_; }
  const Status& status() const { return status_; }

  static Response StockResponse(Status status);

 private:
  virtual std::string GetStartLine() const;

  std::string StatusString() const;
  std::string ContentString() const;

  Status status_;

  static logger::Logger logger_;
};

}  // namespace http

#endif  // SRC_HTTP_RESPONSE_H_

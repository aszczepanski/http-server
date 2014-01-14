#ifndef SRC_HTTP_REQUEST_H_
#define SRC_HTTP_REQUEST_H_

#include "http/message.h"

#include <string>
#include <vector>

#include "http/header.h"

namespace http {

class Request : public Message {
 public:
  enum Method {
    OPTIONS,
    GET,
    HEAD,
    POST,
    PUT,
    DELETE,
    TRACE,
    CONNECT
  };

  Method& method() { return method_; }
  const Method& method() const { return method_; }

  std::string& uri() { return uri_; }
  const std::string& uri() const { return uri_; }

 private:
  virtual std::string GetStartLine() const;

  Method method_;
  std::string uri_;
};

}  // namespace http

#endif  // SRC_HTTP_REQUEST_H_

#ifndef SRC_HTTP_REQUEST_H_
#define SRC_HTTP_REQUEST_H_

#include <string>
#include <vector>
#include "http/header.h"

namespace http {

enum Method {
  GET
};

class Request {
 public:
  Method& method() { return method_; }
  const Method& method() const { return method_; }

  std::string& uri() { return uri_; }
  const std::string& uri() const { return uri_; }

  int& http_version_major() { return http_version_major_; }
  const int& http_version_major() const { return http_version_major_; }

  int& http_version_minor() { return http_version_minor_; }
  const int& http_version_minor() const { return http_version_minor_; }

  std::vector<Header>& headers() { return headers_; }
  const std::vector<Header>& headers() const { return headers_; }

 private:
  Method method_;
  std::string uri_;
  int http_version_major_;
  int http_version_minor_;
  std::vector<Header> headers_;
};

}  // namespace http

#endif  // SRC_HTTP_REQUEST_H_

#ifndef SRC_HTTP_REQUEST_H_
#define SRC_HTTP_REQUEST_H_

#include <string>
#include <vector>
#include "http/header.h"

namespace http {

  class Request {
   public:
    std::string method;
    std::string uri;
    int http_version_major;
    int http_version_minor;
    std::vector<Header> headers;
  };

}  // namespace http

#endif  // SRC_HTTP_REQUEST_H_

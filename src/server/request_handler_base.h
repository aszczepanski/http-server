#ifndef SRC_SERVER_REQUEST_HANDLER_BASE_H_
#define SRC_SERVER_REQUEST_HANDLER_BASE_H_

#include <string>

#include "logger/logger.h"

namespace http {
class Request;
class Response;
}  // namespace http

namespace server {

class RequestHandlerBase {
 public:
  RequestHandlerBase();
  virtual ~RequestHandlerBase();

  virtual void HandleRequest(const http::Request& request, http::Response* response) const;

 protected:
  std::string root_directory_;

 private:
  static logger::Logger logger_;
};

}  // namespace server

#endif  // SRC_SERVER_REQUEST_HANDLER_BASE_H_

#ifndef SRC_SERVER_REQUEST_HANDLER_HEAD_H_
#define SRC_SERVER_REQUEST_HANDLER_HEAD_H_

#include "server/request_handler_get.h"

#include <string>

#include "logger/logger.h"

namespace server {

class RequestHandlerHEAD : public RequestHandlerGET {
 public:
  virtual void HandleRequest(const http::Request& request, http::Response* response) const;

  static logger::Logger logger_;
};

}  // namespace server

#endif  // SRC_SERVER_REQUEST_HANDLER_HEAD_H_

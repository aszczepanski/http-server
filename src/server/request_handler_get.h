#ifndef SRC_SERVER_REQUEST_HANDLER_GET_H_
#define SRC_SERVER_REQUEST_HANDLER_GET_H_

#include "server/request_handler_base.h"

#include "logger/logger.h"

namespace server {

class RequestHandlerGET : public RequestHandlerBase {
 public:
  virtual void HandleRequest(const http::Request& request, http::Reply* reply) const;

 private:
  static logger::Logger logger_;
};

}  // namespace server

#endif  // SRC_SERVER_REQUEST_HANDLER_GET_H_
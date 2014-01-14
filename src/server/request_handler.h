#ifndef SRC_SERVER_REQUEST_HANDLER_H_
#define SRC_SERVER_REQUEST_HANDLER_H_

#include "server/request_handler_base.h"
#include "server/request_handler_get.h"

#include "logger/logger.h"

namespace http {
class Request;
class Reply;
}  // namespace http

namespace server {

class RequestHandler : public RequestHandlerBase {
 public:
  RequestHandler();
  virtual ~RequestHandler();

  virtual void HandleRequest(const http::Request& request, http::Reply* reply) const;

 private:
  RequestHandler(const RequestHandler&);
  RequestHandler& operator=(const RequestHandler&);

  RequestHandlerGET request_handler_get_;

  static const logger::Logger logger_;
};

}  // namespace server

#endif  // SRC_SERVER_REQUEST_HANDLER_H_

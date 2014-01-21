#ifndef SRC_SERVER_REQUEST_HANDLER_H_
#define SRC_SERVER_REQUEST_HANDLER_H_

#include "server/request_handler_base.h"
#include "server/request_handler_delete.h"
#include "server/request_handler_get.h"
#include "server/request_handler_post.h"
#include "server/request_handler_put.h"

#include "logger/logger.h"

namespace http {
class Request;
class Response;
}  // namespace http

namespace server {

class RequestHandler : public RequestHandlerBase {
 public:
  RequestHandler();
  virtual ~RequestHandler();

  virtual void HandleRequest(const http::Request& request, http::Response* response) const;

 private:
  RequestHandler(const RequestHandler&);
  RequestHandler& operator=(const RequestHandler&);

  RequestHandlerDELETE request_handler_delete_;
  RequestHandlerGET request_handler_get_;
  RequestHandlerPOST request_handler_post_;
  RequestHandlerPUT request_handler_put_;

  static const logger::Logger logger_;
};

}  // namespace server

#endif  // SRC_SERVER_REQUEST_HANDLER_H_

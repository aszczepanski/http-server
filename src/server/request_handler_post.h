#ifndef SRC_SERVER_REQUEST_HANDLER_POST_H_
#define SRC_SERVER_REQUEST_HANDLER_POST_H_

#include "server/request_handler_base.h"

#include "logger/logger.h"

namespace server {

class RequestHandlerPOST : public RequestHandlerBase {
 private:
  static logger::Logger logger_;
};

}  // namespace server

#endif  // SRC_SERVER_REQUEST_HANDLER_POST_H_

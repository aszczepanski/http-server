#ifndef SRC_SERVER_REQUEST_HANDLER_PUT_H_
#define SRC_SERVER_REQUEST_HANDLER_PUT_H_

#include "server/request_handler_base.h"

#include <string>

#include "logger/logger.h"

namespace server {

class RequestHandlerPUT : public RequestHandlerBase {
 public:
  virtual void HandleRequest(const http::Request& request, http::Response* response) const;

 private:
  void WriteFile(const std::string& full_path, const char* content, http::Response* response) const;

  static logger::Logger logger_;
};

}  // namespace server

#endif  // SRC_SERVER_REQUEST_HANDLER_PUT_H_

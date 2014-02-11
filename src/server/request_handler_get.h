#ifndef SRC_SERVER_REQUEST_HANDLER_GET_H_
#define SRC_SERVER_REQUEST_HANDLER_GET_H_

#include "server/request_handler_base.h"

#include <string>

#include "logger/logger.h"

namespace server {

class RequestHandlerGET : public RequestHandlerBase {
 public:
  virtual void HandleRequest(const http::Request& request, http::Response* response) const;

 private:
  void CreateResponse(
    const std::string& full_path, http::Response* response) const;
  void CreateNormalResponse(
    const std::string& full_path, http::Response* response) const;
  void CreatePHPResponse(
    const std::string& full_path, http::Response* response) const;

  static logger::Logger logger_;
};

}  // namespace server

#endif  // SRC_SERVER_REQUEST_HANDLER_GET_H_

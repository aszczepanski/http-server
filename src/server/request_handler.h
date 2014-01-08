#ifndef SRC_SERVER_REQUEST_HANDLER_H_
#define SRC_SERVER_REQUEST_HANDLER_H_

#include <libconfig.h++>
#include <string>

namespace http {
class Request;
class Reply;
}  // namespace http

namespace server {

class RequestHandler {
 public:
  explicit RequestHandler(const libconfig::Config& config);
  void HandleRequest(const http::Request& request, http::Reply* reply);

 private:
  RequestHandler(const RequestHandler&);
  RequestHandler& operator=(const RequestHandler&);

  std::string root_directory_;
};

}  // namespace server

#endif  // SRC_SERVER_REQUEST_HANDLER_H_

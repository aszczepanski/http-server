#include "server/request_handler_trace.h"

#include "http/request.h"
#include "http/response.h"

namespace server {

logger::Logger RequestHandlerTRACE::logger_("server.request_handler_post");

void RequestHandlerTRACE::HandleRequest(
    const http::Request& request, http::Response* response) const {
}

}  // namespace server

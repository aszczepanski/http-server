#ifndef SRC_SERVER_ACCEPTOR_EXCEPTIONS_H_
#define SRC_SERVER_ACCEPTOR_EXCEPTIONS_H_

#include <stdexcept>

namespace server {

typedef std::runtime_error AcceptorError;

class AcceptError : public AcceptorError {
 public:
  explicit AcceptError(const char* error)
    : AcceptorError(error) {
  }
};

}  // namespace server

#endif  // SRC_SERVER_ACCEPTOR_EXCEPTIONS_H_

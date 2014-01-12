#ifndef SRC_SERVER_ACCEPTOR_EXCEPTIONS_H_
#define SRC_SERVER_ACCEPTOR_EXCEPTIONS_H_

#include <stdexcept>

namespace server {

class AcceptError : public std::runtime_error {
 public:
  explicit AcceptError(const char* error)
    : std::runtime_error(error) {
  }
};

}  // namespace server

#endif  // SRC_SERVER_ACCEPTOR_EXCEPTIONS_H_

#ifndef SRC_HTTP_HEADER_H_
#define SRC_HTTP_HEADER_H_

#include <string>

namespace http {

struct Header {
 public:
  std::string& key() { return key_; }
  const std::string& key() const { return key_; }

  std::string& value() { return value_; }
  const std::string& value() const { return value_; }

 private:
  std::string key_;
  std::string value_;
};

}  // namespace http

#endif  // SRC_HTTP_HEADER_H_

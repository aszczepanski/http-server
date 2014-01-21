#ifndef SRC_HTTP_MIME_H_
#define SRC_HTTP_MIME_H_

#include <string>
#include <map>

namespace http {

class Mime {
 public:
  static Mime& GetInstance();

  std::string GetType(const std::string& extension);

 private:
  Mime();

  Mime(const Mime&) = delete;
  Mime& operator=(const Mime&) = delete;

  std::map<std::string, std::string> mime_types_;
};

}  // namespace http

#endif  // SRC_HTTP_MIME_H_

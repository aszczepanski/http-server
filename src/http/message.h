#ifndef SRC_HTTP_MESSAGE_H_
#define SRC_HTTP_MESSAGE_H_

#include <string>
#include <vector>

#include "http/header.h"
#include "logger/logger.h"

namespace http {

class Message {
 public:
  Message();
  virtual ~Message();

  std::string ToString() const;

  int& http_version_major() { return http_version_major_; }
  const int& http_version_major() const { return http_version_major_; }

  int& http_version_minor() { return http_version_minor_; }
  const int& http_version_minor() const { return http_version_minor_; }

  std::vector<Header>& headers() { return headers_; }
  const std::vector<Header>& headers() const { return headers_; }

  std::string& content() { return content_; }
  const std::string& content() const { return content_; }

 protected:
  virtual std::string GetStartLine() const = 0;

  int http_version_major_;
  int http_version_minor_;
  std::vector<Header> headers_;
  std::string content_;

  static logger::Logger logger_;
};

}  // namespace http

#endif  // SRC_HTTP_MESSAGE_H_

#ifndef SRC_HTTP_HEADER_H_
#define SRC_HTTP_HEADER_H_

#include <string>

namespace http {

  struct Header {
    std::string key;
    std::string value;
  };

}

#endif  // SRC_HTTP_HEADER_H_

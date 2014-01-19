#include "http/message.h"

#include <string>

#include "logger/logger.h"

using http::Message;
using std::string;

logger::Logger Message::logger_("http.message");

Message::Message() {
}

Message::~Message() {
}

static const string separator = { ':', ' ' };
static const string crlf = { '\r', '\n' };

std::string Message::ToString() const {
  std::string result;

  result += GetStartLine();

  for (auto h : headers_) {
    result += h.key();
    result += separator;
    result += h.value();
    result += crlf;
  }

  result += crlf;
  result += content_;

// LOG_DEBUG(logger_, "Message ToString: \n" << result)

  return result;
}

#include "logger/logger.h"

#include <iostream>
#include <string>

#include "thread/mutex.h"

using logger::Logger;

Logger::Logger(const std::string& name)
  : name_(name) {
}

void Logger::log(kMessageLevel message_level, const std::string& msg,
    pthread_t thread_id, int line_number,
    const std::string& file_name) const {
  mutex_.Lock();

  std::cout << MessageLevelToStr(message_level) << " "
    << name_ << " "
    << "[" << (unsigned int)thread_id << "] "
    << msg << " "
    << std::endl;

  mutex_.Unlock();
}

std::string Logger::MessageLevelToStr(kMessageLevel message_level) {
  switch (message_level) {
  case INFO:
    return " INFO";
  case WARN:
    return " WARN";
  case ERROR:
    return "ERROR";
  case DEBUG:
    return "DEBUG";
  default:
    return "-----";
  }
}

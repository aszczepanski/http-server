#include "logger/logger.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <chrono>
#include <ctime>

#include "thread/mutex.h"

using logger::Logger;

Logger::Logger(const std::string& name)
  : name_(name) {
}

void Logger::log(kMessageLevel message_level, const std::string& msg,
    pthread_t thread_id, int line_number,
    const std::string& file_name) const {
  using std::chrono::system_clock;

  auto now = system_clock::now();
  std::time_t tt = system_clock::to_time_t(now);

  mutex_.Lock();

  std::cout << std::left;
  std::cout << MessageLevelToStr(message_level) << " "
    << "[" << std::setw(12) << std::setfill('0') << std::right << (unsigned int)thread_id << "] "
    << std::setw(25) << std::setfill(' ') << std::left << name_ << " "
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

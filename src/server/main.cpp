#include "server/server.h"

#include "logger/logger.h"
#include "settings/settings.h"

static const logger::Logger logger_("server.main");

int main() {
  LOG_INFO(logger_, "Entering server application.")

  server::Server server;
  server.Run();

  LOG_INFO(logger_, "Exiting server application.")

  return 0;
}

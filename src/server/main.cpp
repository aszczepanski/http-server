#include "server/server.h"

#include <libconfig.h++>

#include "logger/logger.h"

static logger::Logger logger_("main.main");

int main() {
  LOG_INFO(logger_, "Entering server application.")

  libconfig::Config server_config;
  server_config.readFile("conf/server.conf");

  server::Server server(server_config);
  server.Run();

  LOG_INFO(logger_, "Exiting server application.")

  return 0;
}

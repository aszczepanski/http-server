#include "server/server.h"

#include <libconfig.h++>

int main() {
  libconfig::Config server_config;
  server_config.readFile("conf/server.conf");

  server::Server server(server_config);
  server.run();

  return 0;
}

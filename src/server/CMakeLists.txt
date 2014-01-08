project(sk-http)

set(SRCS_SERVER
  connection.cpp
  connection.h
  connection_manager.cpp
  connection_manager.h
  main.cpp
  request_handler.cpp
  request_handler.h
  request_parser.cpp
  request_parser.h
  server.cpp
  server.h
)

set(LIBS_SERVER
  http
  ${LIBCONFIGPP_LIBRARIES}
  pthread
)

add_executable(server ${SRCS_SERVER})
target_link_libraries(server ${LIBS_SERVER})

add_style_check_target(server "${SRCS_SERVER}" sk-http)

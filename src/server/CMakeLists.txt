project(sk-http)

set(SRCS_SERVER
  server.cpp
)

set(LIBS_SERVER
  http
)

add_executable(server ${SRCS_SERVER})
target_link_libraries(server ${LIBS_SERVER})

add_style_check_target(server "${SRCS_SERVER}" sk-http)

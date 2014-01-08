project(sk-http)

set(SRCS_CLIENT
  main.cpp
)

set(LIBS_CLIENT
  http
)

add_executable(client ${SRCS_CLIENT})
target_link_libraries(client ${LIBS_CLIENT})

add_style_check_target(client "${SRCS_CLIENT}" sk-http)

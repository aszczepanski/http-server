project(sk-http)

set(SRCS_SERVER
  acceptor.cpp
  acceptor.h
  acceptor_exceptions.h
  connection.cpp
  connection.h
  connection_manager.cpp
  connection_manager.h
  main.cpp
  request_handler.cpp
  request_handler.h
  request_handler_base.cpp
  request_handler_base.h
  request_handler_delete.cpp
  request_handler_delete.h
  request_handler_get.cpp
  request_handler_get.h
  request_handler_post.cpp
  request_handler_post.h
  request_handler_put.cpp
  request_handler_put.h
  request_handler_trace.cpp
  request_handler_trace.h
  request_handler_head.cpp
  request_handler_head.h
  request_parser.cpp
  request_parser.h
  server.cpp
  server.h
  socket.cpp
  socket.h
  socket_exceptions.h
)

set(LIBS_SERVER
  http
  thread
  logger
  settings
  ${LIBCONFIGPP_LIBRARIES}
  pthread
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_REGEX_LIBRARY}
)

add_executable(server ${SRCS_SERVER})
target_link_libraries(server ${LIBS_SERVER})

add_style_check_target(server "${SRCS_SERVER}" sk-http)

project(sk-http)

set(SRCS_HTTP
  header.h
  message.cpp
  message.h
  request.cpp
  request.h
  response.cpp
  response.h
)

add_library(http ${SRCS_HTTP})

add_style_check_target(http "${SRCS_HTTP}" sk-http)


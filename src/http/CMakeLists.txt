project(sk-http)

set(SRCS_HTTP
  request.cpp
  request.h
)

add_library(http ${SRCS_HTTP})

add_style_check_target(http "${SRCS_HTTP}" sk-http)


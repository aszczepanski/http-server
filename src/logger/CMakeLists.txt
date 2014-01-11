project(sk-http)

set(SRCS_LOGGER
  logger.cpp
  logger.h
)

set(LIBS_LOGGER
  thread
  pthread
)

add_library(logger ${SRCS_LOGGER})
target_link_libraries(logger ${LIBS_LOGGER})

add_style_check_target(logger "${SRCS_LOGGER}" sk-http)


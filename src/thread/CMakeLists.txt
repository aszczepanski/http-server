project(sk-http)

set(SRCS_THREAD
  mutex.cpp
  mutex.h
  thread_interface.cpp
  thread_interface.h
)

add_library(thread ${SRCS_THREAD})

add_style_check_target(thread "${SRCS_THREAD}" sk-http)


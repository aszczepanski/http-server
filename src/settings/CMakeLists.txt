project(sk-http)

set(SRCS_SETTINGS
  settings.cpp
  settings.h
)

add_library(settings ${SRCS_SETTINGS})

add_style_check_target(settings "${SRCS_SETTINGS}" sk-http)


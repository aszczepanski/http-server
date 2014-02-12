project(sk-http)

find_package(Qt5Widgets)
find_package(Qt5Core)

set(SRCS_CLIENT
  main.cpp
  uploaderwindow.cpp
  uploaderwindow.h
)

QT5_WRAP_UI(UIS_HDRS
  uploaderwindow.ui
)

set(CMAKE_PREFIX_PATH $ENV{QTDIR} ${CMAKE_PREFIX_PATH})

set(LIBS_CLIENT
  http
)

set(CMAKE_AUTOMOC ON)

add_executable(client ${SRCS_CLIENT} ${UIS_HDRS})
target_link_libraries(client ${LIBS_CLIENT})

qt5_use_modules(client Widgets Network)

add_style_check_target(client "${SRCS_CLIENT}" sk-http)

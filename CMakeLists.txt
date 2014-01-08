project(sk-http)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(EnableCXX11)
include(BuildType)
include(StyleCheck)

find_package(LibConfig REQUIRED)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

include_directories(
  src
  ${LOG4CXX_INCLUDE_DIR}
)

# add new directories here
add_subdirectory(src/http)
add_subdirectory(src/server)
add_subdirectory(src/client)


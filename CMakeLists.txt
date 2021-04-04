cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

project (qu)

add_subdirectory (ted)

add_library (qu INTERFACE)

target_link_libraries(qu INTERFACE ted)

target_include_directories(qu INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)

project (qu)

find_package(Git)

if(GIT_FOUND)
  execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                  RESULT_VARIABLE GIT_SUBMOD_RESULT)
  if(NOT GIT_SUBMOD_RESULT EQUAL "0")
      message(FATAL_ERROR "git submodule update failed. please checkout submodules")
  endif()
endif()

add_subdirectory (ted)

add_library (qu INTERFACE)

target_link_libraries(qu INTERFACE ted)

target_include_directories(qu INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
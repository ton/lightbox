cmake_minimum_required(VERSION 2.8)

project(LightBox)

set(SOURCES
  main.cpp)

set(CMAKE_CXX_FLAGS -std=c++0x)

include(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(
  lightbox
  ${SOURCES})

add_custom_command(
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/DroidSansMono.ttf
  COMMAND ${CMAKE_COMMAND} -E copy /usr/share/fonts/TTF/DroidSansMono.ttf ${CMAKE_CURRENT_BINARY_DIR}/DroidSansMono.ttf
  MAIN_DEPENDENCY /usr/share/fonts/TTF/DroidSansMono.ttf)

add_custom_target(DroidFont ALL
  DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/DroidSansMono.ttf)

target_link_libraries(lightbox ${SDL2_LIBRARIES} SDL2_ttf)

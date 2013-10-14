cmake_minimum_required(VERSION 2.8)

project(LightBox)

set(CMAKE_CXX_FLAGS -std=c++0x)

include(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)
include_directories(${SDL2_INCLUDE_DIRS})

# Define the library path for the output.
set(TARGET_BINARY_PATH "${PROJECT_SOURCE_DIR}/build/bin/")
set(TARGET_LIBRARY_PATH "${PROJECT_SOURCE_DIR}/build/lib/")

# Set the output path for libraries.
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/build/lib")

# Set the global include path to the project root path.
include_directories(.)

add_subdirectory(math)
add_subdirectory(core)
add_subdirectory(renderers)
add_subdirectory(ui)

set(SOURCES
  main.cpp
)

add_executable(
  lightbox
  ${SOURCES}
)

add_custom_command(
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/DroidSansMono.ttf
  COMMAND ${CMAKE_COMMAND} -E copy /usr/share/fonts/TTF/DroidSansMono.ttf ${CMAKE_CURRENT_BINARY_DIR}/DroidSansMono.ttf
  MAIN_DEPENDENCY /usr/share/fonts/TTF/DroidSansMono.ttf
)

add_custom_target(DroidFont ALL
  DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/DroidSansMono.ttf
)

target_link_libraries(lightbox ${SDL2_LIBRARIES} SDL2_ttf lb_ui lb_core lb_renderers lb_math)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})

# Add global test binary.
add_executable(run_tests
  tests/main.cpp
)
target_link_libraries(run_tests gtest gtest_main lb_core lb_math)

# Add benchmark binary.
add_executable(ray_triangle_benchmark
  benchmarks/ray_triangle_benchmark.cpp
)
target_link_libraries(ray_triangle_benchmark lb_core lb_math boost_program_options)

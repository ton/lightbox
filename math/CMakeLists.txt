set(SOURCES
  src/vector.cpp)

add_library(lb_math SHARED ${SOURCES})

target_link_libraries(lb_math profiler)

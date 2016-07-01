set(SOURCES
  src/vector_2d.cpp
  src/vector_3d.cpp)

add_library(lb_math SHARED ${SOURCES})

target_link_libraries(lb_math profiler)

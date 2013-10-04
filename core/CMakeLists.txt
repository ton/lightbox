set(SOURCES
  src/mesh.cpp
  src/ray.cpp
  src/triangle.cpp)

add_library(lb_core SHARED ${SOURCES})

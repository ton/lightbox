set(SOURCES
  src/bounding_box.cpp
  src/obj_reader.cpp
  src/mesh.cpp
  src/ray.cpp
  src/triangle.cpp)

add_library(lb_core SHARED ${SOURCES})

target_link_libraries(lb_core profiler)

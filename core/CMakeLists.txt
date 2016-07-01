set(SOURCES
  src/bounding_box.cpp
  src/camera.cpp
  src/obj_reader.cpp

  src/film.cpp

  src/mesh.cpp
  src/ray.cpp
  src/sampling.cpp
  src/scene.cpp
  src/triangle.cpp)

add_library(lb_core SHARED ${SOURCES})

target_link_libraries(lb_core profiler)

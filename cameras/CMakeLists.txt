set(SOURCES
  src/perspective_camera.cpp
  src/pinhole_camera.cpp)

add_library(lb_cameras SHARED ${SOURCES})

target_link_libraries(lb_cameras profiler)

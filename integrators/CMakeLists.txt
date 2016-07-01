set(SOURCES
  src/raycast_integrator.cpp)

add_library(lb_integrators SHARED ${SOURCES})

target_link_libraries(lb_integrators profiler)

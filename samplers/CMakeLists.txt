set(SOURCES
  src/simple_sampler.cpp)

add_library(lb_samplers SHARED ${SOURCES})

target_link_libraries(lb_samplers profiler)

set(SOURCES
  src/static_noise_renderer.cpp
  src/cpu_triangle_renderer.cpp
)

add_library(lb_renderers SHARED ${SOURCES})

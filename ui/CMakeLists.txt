set(SOURCES
  src/window.cpp
  sdl/src/sdl_window.cpp
)

add_library(lb_ui SHARED ${SOURCES})

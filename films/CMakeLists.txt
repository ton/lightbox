set(SOURCES
  src/memory_film.cpp)

add_library(lb_films SHARED ${SOURCES})

target_link_libraries(lb_films profiler)

set(SOURCES
)

add_library(lb_common SHARED ${SOURCES})

target_link_libraries(lb_common profiler)

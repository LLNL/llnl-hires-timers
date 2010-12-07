set(TIMING_SOURCES timing.c)
set(TIMING_HEADERS timing.h)

add_library(timing ${TIMING_SOURCES})
install(TARGETS timing DESTINATION lib)
install(FILES ${TIMING_HEADERS} DESTINATION include)

include_directories(${PROJECT_BINARY_DIR})

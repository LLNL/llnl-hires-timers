set(TIMING_SOURCES timing.c)
set(TIMING_HEADERS timing.h)

add_library(adept-timing ${TIMING_SOURCES})
install(TARGETS adept-timing DESTINATION lib EXPORT adept_utils-libs)
install(FILES ${TIMING_HEADERS} DESTINATION include)

if (CMAKE_COMPILER_ID STREQUAL XL)
  set_target_properties(adept-timing PROPERTIES COMPILE_FLAGS "-qlanglvl=c99")
elseif(CMAKE_COMPILER_ID STREQUAL Intel)
  set_target_properties(adept-timing PROPERTIES COMPILE_FLAGS "-std=c99")
else()
  set_target_properties(adept-timing PROPERTIES COMPILE_FLAGS "-std=gnu99")
endif()

include_directories(${PROJECT_BINARY_DIR})

if (CMAKE_SYSTEM_NAME STREQUAL BlueGeneL)
  include_directories(/bgl/BlueLight/ppcfloor/bglsys/include)
endif()


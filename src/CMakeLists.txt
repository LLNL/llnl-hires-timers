#
# Timing library -- this is in straight C for greater accessibility
#
add_library(adept_timing timing.c)
install(TARGETS adept_timing DESTINATION lib EXPORT adept_utils-libs)
install(FILES timing.h DESTINATION include)

if (CMAKE_C_COMPILER_ID STREQUAL XL)
  set_target_properties(adept_timing PROPERTIES COMPILE_FLAGS "-qlanglvl=extc99")
elseif(CMAKE_COMPILER_ID STREQUAL Intel)
  set_target_properties(adept_timing PROPERTIES COMPILE_FLAGS "-std=c99")
else()
  set_target_properties(adept_timing PROPERTIES COMPILE_FLAGS "-std=gnu99")
endif()

if (CMAKE_SYSTEM_NAME STREQUAL BlueGeneL)
  include_directories(/bgl/BlueLight/ppcfloor/bglsys/include)
endif()

include_directories(
  ${PROJECT_BINARY_DIR}
  ${PROJECT_SOURCE_DIR}/timing)

#
# Timing library -- this is in straight C for greater accessibility
#
add_static_and_shared_library(adept_timing timing.c)
use_c99_for_target(adept_timing)
use_c99_for_target(adept_timing_static)

install(TARGETS adept_timing adept_timing_static
        DESTINATION lib EXPORT adept_utils-libs)
install(FILES timing.h DESTINATION include)

if (CMAKE_SYSTEM_NAME STREQUAL BlueGeneL)
  include_directories(/bgl/BlueLight/ppcfloor/bglsys/include)
endif()

include_directories(${PROJECT_BINARY_DIR}
/bgsys/drivers/ppcfloor/spi/include/kernel/cnk
)

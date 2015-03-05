###############################################################
# Adept Utilities
#
# This project is a set of libraries for commonly useful
# routines for ADEPT code projects.
###############################################################
project(adept-utils)
cmake_minimum_required(VERSION 2.8)


# choose new behaviour for CMP0042
# see http://www.cmake.org/cmake/help/v3.0/policy/CMP0042.html for more details
if (POLICY CMP0042)
  cmake_policy(SET CMP0042 NEW)
endif (POLICY CMP0042)


# Add our module directory to the include path.
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH}")
include(StaticAndShared)
include(C99Support)

# Check for various timing functions, so we can support highest-resolution timers available.
include(CheckFunctionExists)


# Check for various timing functions, so we can support highest-resolution timers available.
include(CheckFunctionExists)

set(CMAKE_REQUIRED_INCLUDES  time.h sys/time.h)
set(CMAKE_REQUIRED_LIBRARIES rt)
check_function_exists(clock_gettime ADEPT_UTILS_HAVE_CLOCK_GETTIME)

set(CMAKE_REQUIRED_INCLUDES  sys/time.h)
unset(CMAKE_REQUIRED_LIBRARIES)
check_function_exists(gettimeofday ADEPT_UTILS_HAVE_GETTIMEOFDAY)

set(CMAKE_REQUIRED_INCLUDES  mach/mach.h mach/mach_time.h)
unset(CMAKE_REQUIRED_LIBRARIES)
check_function_exists(mach_absolute_time ADEPT_UTILS_HAVE_MACH_TIME)

# Configure a header file with all the variables we found.
configure_file(
  ${PROJECT_SOURCE_DIR}/adept-utils-config.h.in
  ${PROJECT_BINARY_DIR}/adept-utils-config.h)
install(FILES ${PROJECT_BINARY_DIR}/adept-utils-config.h DESTINATION include)

# Configure subdirectories here, after everything else, so that they
# inherit variables set in the global scope.
add_subdirectory(timing)
add_subdirectory(test)

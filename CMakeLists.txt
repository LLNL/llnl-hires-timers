###############################################################
# Adept Utilities
#
# This project is a set of libraries for commonly useful 
# routines for ADEPT code projects.
###############################################################
project(adept-utils)
cmake_minimum_required(VERSION 2.8)


# Build shared libraries by default.
get_property(DEFAULT_SHARED GLOBAL PROPERTY TARGET_SUPPORTS_SHARED_LIBS)
option(BUILD_SHARED_LIBS "Build shared libraries?" DEFAULT_SHARED)

# Check for various timing functions, so we can support highest-resolution timers available.
include(CheckFunctionExists)


set(CMAKE_REQUIRED_INCLUDES  time.h sys/time.h)
set(CMAKE_REQUIRED_LIBRARIES rt)
check_function_exists(clock_gettime ADEPT_UTILS_HAVE_CLOCK_GETTIME)

set(CMAKE_REQUIRED_INCLUDES  sys/time.h)
unset(CMAKE_REQUIRED_LIBRARIES)
check_function_exists(gettimeofday ADEPT_UTILS_HAVE_GETTIMEOFDAY)

# Configure a header file with all the variables we found.
configure_file(
  ${PROJECT_SOURCE_DIR}/adept-utils-config.h.in
  ${PROJECT_BINARY_DIR}/adept-utils-config.h)
install(FILES ${PROJECT_BINARY_DIR}/adept-utils-config.h DESTINATION include)

# Configure subdirectories here, after everything else, so that they 
# inherit variables set in the global scope.
add_subdirectory(timing)

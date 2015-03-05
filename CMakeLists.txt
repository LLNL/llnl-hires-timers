# This file is part of hrtimer.
#
# Copyright (c) 2010, Lawrence Livermore National Security, LLC.
# Produced at the Lawrence Livermore National Laboratory
# LLNL-CODE-417602
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
#  - Redistributions of source code must retain the above copyright notice, this
#    list of conditions and the disclaimer below.
#
#  - Redistributions in binary form must reproduce the above copyright notice,
#    this list of conditions and the disclaimer (as noted below) in the
#    documentation and/or other materials provided with the distribution.
#
# - Neither the name of the LLNS/LLNL nor the names of its contributors may be
#   used to endorse or promote products derived from this software without
#   specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL LAWRENCE LIVERMORE NATIONAL SECURITY, LLC,
# THE U.S. DEPARTMENT OF ENERGY OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
# INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
# ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
# Please also read the LICENSE file for further information.
#

# set project name
project(htimer)


# set minimum required CMake version
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
add_subdirectory(src)
add_subdirectory(test)

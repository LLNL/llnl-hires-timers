# This file is part of llnl-hires-timers.
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

## \file
#
# \author Todd Gamblin <tgamblin@llnl.gov>
# \author Alexander Haase <alexander.haase@rwth-aachen.de>
#


#
# determine best platform specific timer
#

# Check for various timing functions, so we can support highest-resolution
# timers available.
include(CheckFunctionExists)
include(CheckSymbolExists)


# BlueGene/L
CHECK_SYMBOL_EXISTS("__blrts__" "" HAVE_BLUEGENE_L)

# BlueGene/P
CHECK_SYMBOL_EXISTS("__bgp__" "" HAVE_BLUEGENE_P)

# BlueGene/Q
CHECK_SYMBOL_EXISTS("__bgq__" "" HAVE_BLUEGENE_Q)

# librt
set(CMAKE_REQUIRED_INCLUDES  time.h sys/time.h)
set(CMAKE_REQUIRED_LIBRARIES rt)
check_function_exists(clock_gettime HAVE_CLOCK_GETTIME)

# gettimeofday
set(CMAKE_REQUIRED_INCLUDES  sys/time.h)
unset(CMAKE_REQUIRED_LIBRARIES)
check_function_exists(gettimeofday HAVE_GETTIMEOFDAY)

# OSX mach
set(CMAKE_REQUIRED_INCLUDES  mach/mach.h mach/mach_time.h)
unset(CMAKE_REQUIRED_LIBRARIES)
check_function_exists(mach_absolute_time HAVE_MACH_TIME)



#
# set required source file by platform
#
set(timing_sources "")
set(timing_libs "")

if (HAVE_BLUEGENE_L)
    set(timing_sources "bluegene_l.c")

elseif (HAVE_BLUEGENE_P)
    set(timing_sources "bluegene_p.c")

elseif (HAVE_BLUEGENE_Q)
    set(timing_sources "bluegene_q.c")

elseif (HAVE_MACH_TIME)
    set(timing_sources "mach.c")

elseif (HAVE_CLOCK_GETTIME)
    set(timing_sources "rt.c")
    set(timing_libs "-lrt")

elseif (HAVE_GETTIMEOFDAY)
    set(timing_sources "gettimeofday.c")

else ()
    message(FATAL_ERROR "No supported timing functions found!")
endif()



#
# build timing library
#
include(StaticAndShared)
add_static_and_shared_library(hires-timers ${timing_sources})

target_link_libraries(hires-timers ${timing_libs})


if (CMAKE_SYSTEM_NAME STREQUAL BlueGeneL)
    include_directories(/bgl/BlueLight/ppcfloor/bglsys/include)
endif()

include_directories(/bgsys/drivers/ppcfloor/spi/include/kernel/cnk)


#
# install library
#
install(TARGETS hires-timers hires-timers_static DESTINATION lib)
install(FILES hires-timers.h DESTINATION include)

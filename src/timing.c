/////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2010, Lawrence Livermore National Security, LLC.
// Produced at the Lawrence Livermore National Laboratory
// LLNL-CODE-417602
// All rights reserved.
//
// This file is part of Libra. For details, see http://github.com/tgamblin/libra.
// Please also read the LICENSE file for further information.
//
// Redistribution and use in source and binary forms, with or without modification, are
// permitted provided that the following conditions are met:
//
//  * Redistributions of source code must retain the above copyright notice, this list of
//    conditions and the disclaimer below.
//  * Redistributions in binary form must reproduce the above copyright notice, this list of
//    conditions and the disclaimer (as noted below) in the documentation and/or other materials
//    provided with the distribution.
//  * Neither the name of the LLNS/LLNL nor the names of its contributors may be used to endorse
//    or promote products derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS
// OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
// LAWRENCE LIVERMORE NATIONAL SECURITY, LLC, THE U.S. DEPARTMENT OF ENERGY OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
// ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
/////////////////////////////////////////////////////////////////////////////////////////////////

///
/// @file timing.c
/// @author Todd Gamblin tgamblin@llnl.gov
/// Implementations for get_time_ns() using platform-specific high-resolution timers.
///

#include "timing.h"
#include "adept-utils-config.h"

#if defined(__blrts__)
    #include "bluegene_l.c"

#elif defined(__bgp__)
    #include "bluegene_p.c"

#elif (defined(__bgq__))
    #include "bluegene_q.c"

#elif (defined(ADEPT_UTILS_HAVECLOCK_GETTIME) || defined(ADEPT_UTILS_HAVELIBRT))
    #include "linux.c"

#elif defined(ADEPT_UTILS_HAVE_MACH_TIME)
    #include "mach.c"

#elif defined(ADEPT_UTILS_HAVE_GETTIMEOFDAY)
    #include "gettimeofday.c"

#else
    // if we get to here, we don't even have gettimeofday.
    #error "NO SUPPORTED TIMING FUNCTIONS FOUND!"

#endif // types of timers

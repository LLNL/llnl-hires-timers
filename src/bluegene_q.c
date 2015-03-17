/* This file is part of llnl-hires-timers.
 *
 * Copyright (c) 2010, Lawrence Livermore National Security, LLC.
 * Produced at the Lawrence Livermore National Laboratory
 * LLNL-CODE-417602
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the disclaimer below.
 *
 * - Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the disclaimer (as noted below) in the
 *   documentation and/or other materials provided with the distribution.
 *
 * - Neither the name of the LLNS/LLNL nor the names of its contributors may be
 *   used to endorse or promote products derived from this software without
 *   specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL LAWRENCE LIVERMORE NATIONAL SECURITY, LLC,
 * THE U.S. DEPARTMENT OF ENERGY OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Please also read the LICENSE file for further information.
 */

/** \file
 *
 * \author Vivek L. Kale <kale2@rzuseqlac2.llnl.gov>
 */


#ifndef __bgq__
	#error "This file needs a BlueGene/L environment"
#endif

#include "hires-timers.h"
#include "bluegene_q.h"

#include <hwi/include/bqc/A2_core.h> // This gets us the register names on A2.


// These calls keep the compiler from moving instructions before or after the
// location where they're called in the code. This increases the "honesty" of
// the measurement.
#ifdef __xlc__
	// This is an XLC builtin function
	#define memory_fence() __fence()
#else
	// This is a GNU inline assembler statement
	#define memory_fence() asm __volatile__ ("" ::: "memory")
#endif


// 64-bit read of BGQ Cycle counter register.
#define get_bgq_cycles(dest) \
	memory_fence(); \
	asm volatile ("mfspr %0,%1" : "=&r" (dest) : "i" (SPRN_TBRO)); \
	memory_fence();


// get a timestamp in nanoseconds.  Note that this doesn't represent
// a particular time; it's only useful for taking differences.
timing_t get_time_ns() {
	uint64_t timebase;
	get_bgq_cycles(timebase);
	return timebase * BGQ_NS_PER_CYCLE;
}

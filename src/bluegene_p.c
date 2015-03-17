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
 * \author Todd Gamblin <tgamblin@llnl.gov>
 */


#ifndef __bgp__
	#error "This file needs a BlueGene/P environment"
#endif


#include "hires-timers.h"
#include "bluegene_p.h"

#include <math.h>


typedef union {
	unsigned int ul[2];
	unsigned long long ull;
} bgp_time_reg_t;



#define _bgp_mfspr(SPRN) ({ \
	unsigned int tmp; \
	do { \
		asm volatile ("mfspr %0,%1" : "=&r" (tmp) : "i" (SPRN) : "memory" ); \
	} while(0); \
	tmp; \
})



static inline unsigned long long
timebase()
{
	bgp_time_reg_t reg;
	unsigned int utmp;

	do {
		utmp      = _bgp_mfspr(SPRN_TBRU);
		reg.ul[1] = _bgp_mfspr(SPRN_TBRL);
		reg.ul[0] = _bgp_mfspr(SPRN_TBRU);
	}
	while( utmp != reg.ul[0] );

	return reg.ull;
}

timing_t get_time_ns() {
	return llround(BGP_NS_PER_CYCLE * timebase());
}

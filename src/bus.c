// SPDX-License-Identifier: MIT
//
// Copyright 2024 lunaspis
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the “Software”), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <string.h>
#include "bus.h"
#include "dbg_log.h"

// clang-format off

#define BIOS_BEG	(PSYCHO_BUS_BIOS_BEG)
#define BIOS_END	(PSYCHO_BUS_BIOS_END)
#define BIOS_MASK	(0x000FFFFF)

// clang-format on

u32 bus_lw(struct psycho_ctx *const ctx, const u32 paddr)
{
	u32 word = 0xFFFFFFFF;

	switch (paddr) {
	case BIOS_BEG ... BIOS_END:
		memcpy(&word, &ctx->bus.bios[paddr & BIOS_MASK], sizeof(u32));
		break;

	default:
		LOG_TRACE("Unknown physical address 0x%08X when attempting to "
			  "load word; returning 0xFFFF'FFFF",
			  word, paddr);
		return word;
	}

	LOG_TRACE("Loaded word 0x%08X from physical address 0x%08X", word,
		  paddr);
	return word;
}

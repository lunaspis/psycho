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

#define RAM_BEG		(PSYCHO_BUS_RAM_BEG)
#define RAM_END		(PSYCHO_BUS_RAM_END)

#define BIOS_BEG	(PSYCHO_BUS_BIOS_BEG)
#define BIOS_END	(PSYCHO_BUS_BIOS_END)
#define BIOS_MASK	(0x000FFFFF)

// clang-format on

u32 bus_lw(const struct psycho_ctx *const ctx, const u32 paddr)
{
	u32 word = 0xFFFFFFFF;

	switch (paddr) {
	case RAM_BEG ... RAM_END:
		memcpy(&word, &ctx->bus.ram[paddr], sizeof(u32));
		break;

	case BIOS_BEG ... BIOS_END:
		memcpy(&word, &ctx->bus.bios[paddr & BIOS_MASK], sizeof(u32));
		break;

	default:
		LOG_WARN("Unknown physical address 0x%08X when attempting to "
			 "load word; returning 0xFFFF'FFFF",
			 paddr);
		return word;
	}

	LOG_TRACE("Loaded word 0x%08X from physical address 0x%08X", word,
		  paddr);
	return word;
}

u8 bus_lb(const struct psycho_ctx *const ctx, const u32 paddr)
{
	u8 byte = 0xFF;

	switch (paddr) {
	case RAM_BEG ... RAM_END:
		byte = ctx->bus.ram[paddr];
		break;

	case BIOS_BEG ... BIOS_END:
		byte = ctx->bus.bios[paddr & BIOS_MASK];
		break;

	default:
		LOG_WARN("Unknown physical address 0x%08X when attempting to "
			 "load byte; returning 0xFF",
			 paddr);
		return byte;
	}

	LOG_TRACE("Loaded byte 0x%02X from 0x%08X", byte, paddr);
	return byte;
}

void bus_sw(struct psycho_ctx *const ctx, const u32 paddr, const u32 word)
{
	switch (paddr) {
	case RAM_BEG ... RAM_END:
		memcpy(&ctx->bus.ram[paddr], &word, sizeof(u32));
		break;

	default:
		LOG_WARN("Unknown physical address 0x%08X when attempting to "
			 "store word 0x%08X; ignoring",
			 paddr, word);
		return;
	}
	LOG_TRACE("Stored word 0x%08X at 0x%08X", word, paddr);
}

void bus_sh(struct psycho_ctx *const ctx, const u32 paddr, const u16 hword)
{
	LOG_WARN("Unknown physical address 0x%08X when attempting to store "
		 "half-word 0x%04X; ignoring",
		 paddr, hword);
}

void bus_sb(struct psycho_ctx *const ctx, const u32 paddr, const u8 byte)
{
	switch (paddr) {
	case RAM_BEG ... RAM_END:
		ctx->bus.ram[paddr] = byte;
		break;

	default:
		LOG_WARN("Unknown physical address 0x%08X when attempting to "
			 "store byte 0x%02X; ignoring",
			 paddr, byte);
		break;
	}
	LOG_TRACE("Stored byte 0x%02X at 0x%08X", byte, paddr);
}

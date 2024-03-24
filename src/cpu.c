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

#include "cpu.h"
#include "cpu_defs.h"
#include "bus.h"

// clang-format off

#define PC 	(ctx->cpu.pc)
#define GPR	(ctx->cpu.gpr)

// clang-format on

static ALWAYS_INLINE NODISCARD u32 instr_fetch(struct psycho_ctx *const ctx)
{
	const u32 paddr = cpu_vaddr_to_paddr(PC);
	return bus_lw(ctx, paddr);
}

void cpu_reset(struct psycho_ctx *const ctx)
{
	memset(GPR, 0, sizeof(GPR));
	PC = CPU_VEC_RST;

	ctx->cpu.instr = instr_fetch(ctx);
}

void cpu_step(struct psycho_ctx *const ctx)
{
}
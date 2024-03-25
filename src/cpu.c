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
#include "dbg_log.h"

// clang-format off

#define ORI	(CPU_OP_ORI)
#define LUI	(CPU_OP_LUI)

#define PC 	(ctx->cpu.pc)
#define GPR	(ctx->cpu.gpr)

#define RI	(PSYCHO_CPU_EXC_CODE_RI)

#define EXC_RAISE(exc_code)	(exc_raise(ctx, (exc_code)))

// clang-format on

const char *const exc_code_names[] = { [RI] = "Reserved instruction" };

static void exc_raise(struct psycho_ctx *const ctx, const uint exc_code)
{
	// Note that in an emulation context, we may not want to actually
	// service an exception. If the frontend cares about the state of the
	// system at the time of the exception, servicing the exception will
	// modify CPU registers and the program counter which may not be
	// desirable.
	//
	// On the other hand, if a test program is being executed, it is
	// possible that exceptions will be raised to test the quality of the
	// implementation; in that context, it is not an error.
	//
	// This necessitates the need at the discretion of the frontend to
	// determine what exceptions actually *halt* execution.
	if (ctx->cpu.exc_halt & (1 << exc_code)) {
		LOG_ERR("%s exception raised!", exc_code_names[exc_code]);
		return;
	}
}

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
	LOG_INFO("CPU reset!");
}

void cpu_step(struct psycho_ctx *const ctx)
{
#define op (cpu_instr_op_get(ctx->cpu.instr))
#define rt (cpu_instr_rt_get(ctx->cpu.instr))
#define rs (cpu_instr_rs_get(ctx->cpu.instr))
#define ZEXT_IMM (cpu_instr_zext_imm_get(ctx->cpu.instr))

	switch (op) {
	case ORI:
		GPR[rt] = GPR[rs] | ZEXT_IMM;
		break;

	case LUI:
		GPR[rt] = ZEXT_IMM << 16;
		break;

	default:
		EXC_RAISE(RI);
		break;
	}
	PC += sizeof(u32);
	ctx->cpu.instr = instr_fetch(ctx);
}

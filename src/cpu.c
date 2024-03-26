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

#include <stdbool.h>
#include <string.h>

#include "cpu.h"
#include "cpu_defs.h"
#include "bus.h"
#include "dbg_log.h"

// clang-format off

#define ra	(CPU_GPR_ra)

#define GROUP_SPECIAL	(CPU_OP_GROUP_SPECIAL)
#define GROUP_BCOND	(CPU_OP_GROUP_BCOND)
#define GROUP_COP0	(CPU_OP_GROUP_COP0)

#define ADD	(CPU_OP_ADD)
#define ADDI	(CPU_OP_ADDI)
#define ADDIU	(CPU_OP_ADDIU)
#define ADDU	(CPU_OP_ADDU)
#define AND	(CPU_OP_AND)
#define ANDI	(CPU_OP_ANDI)
#define BEQ	(CPU_OP_BEQ)
#define BGTZ	(CPU_OP_BGTZ)
#define BLEZ	(CPU_OP_BLEZ)
#define BNE	(CPU_OP_BNE)
#define DIV	(CPU_OP_DIV)
#define DIVU	(CPU_OP_DIVU)
#define J	(CPU_OP_J)
#define JAL	(CPU_OP_JAL)
#define JALR	(CPU_OP_JALR)
#define JR	(CPU_OP_JR)
#define OR	(CPU_OP_OR)
#define ORI	(CPU_OP_ORI)
#define LB	(CPU_OP_LB)
#define LBU	(CPU_OP_LBU)
#define LUI	(CPU_OP_LUI)
#define LW	(CPU_OP_LW)
#define MF	(CPU_OP_MF)
#define MFHI	(CPU_OP_MFHI)
#define MFLO	(CPU_OP_MFLO)
#define MT	(CPU_OP_MT)
#define SB	(CPU_OP_SB)
#define SH	(CPU_OP_SH)
#define SLL	(CPU_OP_SLL)
#define SLT	(CPU_OP_SLT)
#define SLTI	(CPU_OP_SLTI)
#define SLTIU	(CPU_OP_SLTIU)
#define SLTU	(CPU_OP_SLTU)
#define SRA	(CPU_OP_SRA)
#define SRL	(CPU_OP_SRL)
#define SUBU	(CPU_OP_SUBU)
#define SW	(CPU_OP_SW)

#define NPC	(ctx->cpu.npc)
#define PC 	(ctx->cpu.pc)
#define GPR	(ctx->cpu.gpr)

#define CP0_CPR	(ctx->cpu.cp0_cpr)

#define RI	(PSYCHO_CPU_EXC_CODE_RI)

#define EXC_RAISE(exc_code)	(exc_raise(ctx, (exc_code)))
#define BRANCH_IF(cond)		(branch_if(ctx, (cond)))

#define HI	(ctx->cpu.hi)
#define LO	(ctx->cpu.lo)

#define base (cpu_instr_base_get(ctx->cpu.instr))

#define SR	(CP0_CPR[CPU_CP0_CPR_REG_SR])
#define IsC	(CPU_CP0_CPR_REG_SR_IsC)

// clang-format on

const char *const exc_code_names[] = { [RI] = "Reserved instruction" };

static void branch_if(struct psycho_ctx *const ctx, const bool condition_met)
{
	if (condition_met) {
		NPC = cpu_branch_tgt_get(ctx->cpu.instr, PC);
	}
}

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

static ALWAYS_INLINE NODISCARD u32 vaddr_get(struct psycho_ctx *const ctx)
{
	const u32 offset = cpu_instr_offset_get(ctx->cpu.instr);
	return GPR[base] + offset;
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
	NPC = PC + sizeof(u32);

	ctx->cpu.instr = instr_fetch(ctx);
	LOG_INFO("CPU reset!");
}

void cpu_step(struct psycho_ctx *const ctx)
{
#define op (cpu_instr_op_get(ctx->cpu.instr))
#define rt (cpu_instr_rt_get(ctx->cpu.instr))
#define rs (cpu_instr_rs_get(ctx->cpu.instr))
#define rd (cpu_instr_rd_get(ctx->cpu.instr))
#define funct (cpu_instr_funct_get(ctx->cpu.instr))
#define shamt (cpu_instr_shamt_get(ctx->cpu.instr))
#define ZEXT_IMM (cpu_instr_zext_imm_get(ctx->cpu.instr))
#define SEXT_IMM (cpu_instr_sext_imm_get(ctx->cpu.instr))

	PC = (u32)(NPC - sizeof(u32));
	NPC += sizeof(u32);

	switch (op) {
	case GROUP_SPECIAL:
		switch (funct) {
		case SLL:
			GPR[rd] = GPR[rt] << shamt;
			break;

		case SRL:
			GPR[rd] = GPR[rt] >> shamt;
			break;

		case SRA:
			GPR[rd] = (u32)((s32)GPR[rt] >> shamt);
			break;

		case JR:
			NPC = GPR[rs];
			break;

		case JALR: {
			const u32 jump_target = GPR[rs];

			GPR[rd] = PC + 8;

			NPC = jump_target;
			break;
		}

		case MFHI:
			GPR[rd] = HI;
			break;

		case MFLO:
			GPR[rd] = LO;
			break;

		case DIV:
			LO = (u32)((s32)GPR[rs] / (s32)GPR[rt]);
			HI = (u32)((s32)GPR[rs] % (s32)GPR[rt]);

			break;

		case DIVU:
			LO = GPR[rs] / GPR[rt];
			HI = GPR[rs] % GPR[rt];

			break;

		case ADD:
		case ADDU:
			GPR[rd] = GPR[rs] + GPR[rt];
			break;

		case SUBU:
			GPR[rd] = GPR[rs] - GPR[rt];
			break;

		case AND:
			GPR[rd] = GPR[rs] & GPR[rt];
			break;

		case OR:
			GPR[rd] = GPR[rs] | GPR[rt];
			break;

		case SLT:
			GPR[rd] = (s32)GPR[rs] < (s32)GPR[rt];
			break;

		case SLTU:
			GPR[rd] = GPR[rs] < GPR[rt];
			break;

		default:
			EXC_RAISE(RI);
			break;
		}
		break;

	case GROUP_BCOND: {
		const bool cond_met = ((s32)GPR[rs] < 0) ^ (rt & 1);

		if ((rt >> 4) & 1) {
			GPR[ra] = PC + 8;
		}

		BRANCH_IF(cond_met);
		break;
	}

	case J:
		NPC = cpu_jmp_tgt_get(ctx->cpu.instr, PC);
		break;

	case JAL:
		GPR[ra] = PC + 8;
		NPC = cpu_jmp_tgt_get(ctx->cpu.instr, PC);

		break;

	case BEQ:
		BRANCH_IF(GPR[rs] == GPR[rt]);
		break;

	case BNE:
		BRANCH_IF(GPR[rs] != GPR[rt]);
		break;

	case BLEZ:
		BRANCH_IF((s32)GPR[rs] <= 0);
		break;

	case BGTZ:
		BRANCH_IF((s32)GPR[rs] > 0);
		break;

	case ORI:
		GPR[rt] = GPR[rs] | ZEXT_IMM;
		break;

	case ADDI:
	case ADDIU:
		GPR[rt] = GPR[rs] + SEXT_IMM;
		break;

	case SLTI:
		GPR[rt] = (s32)GPR[rs] < (s32)SEXT_IMM;
		break;

	case SLTIU:
		GPR[rt] = GPR[rs] < SEXT_IMM;
		break;

	case ANDI:
		GPR[rt] = GPR[rs] & ZEXT_IMM;
		break;

	case LUI:
		GPR[rt] = ZEXT_IMM << 16;
		break;

	case GROUP_COP0:
		switch (rs) {
		case MF:
			GPR[rt] = CP0_CPR[rd];
			break;

		case MT:
			CP0_CPR[rd] = GPR[rt];
			break;

		default:
			EXC_RAISE(RI);
			break;
		}
		break;

	case LB: {
		const u32 vaddr = vaddr_get(ctx);
		const u32 paddr = cpu_vaddr_to_paddr(vaddr);

		GPR[rt] = (u32)(s8)bus_lb(ctx, paddr);
		break;
	}

	case LW: {
		const u32 vaddr = vaddr_get(ctx);
		const u32 paddr = cpu_vaddr_to_paddr(vaddr);

		GPR[rt] = bus_lw(ctx, paddr);
		break;
	}

	case LBU: {
		const u32 vaddr = vaddr_get(ctx);
		const u32 paddr = cpu_vaddr_to_paddr(vaddr);

		GPR[rt] = bus_lb(ctx, paddr);
		break;
	}

	case SB: {
		const u32 vaddr = vaddr_get(ctx);
		const u32 paddr = cpu_vaddr_to_paddr(vaddr);

		bus_sb(ctx, paddr, (u8)GPR[rt]);
		break;
	}

	case SH: {
		const u32 vaddr = vaddr_get(ctx);
		const u32 paddr = cpu_vaddr_to_paddr(vaddr);

		bus_sh(ctx, paddr, (u16)GPR[rt]);
		break;
	}

	case SW: {
		if (SR & IsC) {
			break;
		}

		const u32 vaddr = vaddr_get(ctx);
		const u32 paddr = cpu_vaddr_to_paddr(vaddr);

		bus_sw(ctx, paddr, GPR[rt]);
		break;
	}

	default:
		EXC_RAISE(RI);
		break;
	}
	PC += sizeof(u32);
	ctx->cpu.instr = instr_fetch(ctx);
}

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

/// @file cpu_defs.h Defines CPU related constants and functions that are useful
/// to both the disassembler and CPU implementations.

#pragma once

#include "compiler.h"
#include "psycho/types.h"

// clang-format off

///@{
/// @brief CPU instruction groups.
/// These are accessed via the "op" field of the instruction.
#define CPU_OP_GROUP_SPECIAL	(0x00)
#define CPU_OP_GROUP_BCOND	(0x01)
#define CPU_OP_GROUP_COP0	(0x10)
#define CPU_OP_GROUP_COP2	(0x12)
///@}

#define CPU_OP_ADD 	(0x20)
#define CPU_OP_ADDI	(0x08)
#define CPU_OP_ADDIU	(0x09)
#define CPU_OP_ADDU	(0x21)
#define CPU_OP_AND	(0x24)
#define CPU_OP_ANDI	(0x0C)
#define CPU_OP_AVSZ3	(0x2D)
#define CPU_OP_AVSZ4	(0x2E)
#define CPU_OP_BEQ	(0x04)
#define CPU_OP_BGTZ	(0x07)
#define CPU_OP_BLEZ	(0x06)
#define CPU_OP_BNE	(0x05)
#define CPU_OP_BREAK	(0x0D)
#define CPU_OP_CC	(0x1C)
#define CPU_OP_CDP	(0x14)
#define CPU_OP_CF	(0x02)
#define CPU_OP_CT	(0x06)
#define CPU_OP_DCPL	(0x29)
#define CPU_OP_DIV	(0x1A)
#define CPU_OP_DIVU	(0x1B)
#define CPU_OP_DPCS	(0x10)
#define CPU_OP_DPCT	(0x2A)
#define CPU_OP_GPF	(0x3D)
#define CPU_OP_GPL	(0x3E)
#define CPU_OP_INTPL	(0x11)
#define CPU_OP_J	(0x02)
#define CPU_OP_JAL	(0x03)
#define CPU_OP_JALR	(0x09)
#define CPU_OP_JR	(0x08)
#define CPU_OP_LB	(0x20)
#define CPU_OP_LBU	(0x24)
#define CPU_OP_LH	(0x21)
#define CPU_OP_LHU	(0x25)
#define CPU_OP_LUI	(0x0F)
#define CPU_OP_LW	(0x23)
#define CPU_OP_LWC2	(0x32)
#define CPU_OP_LWL	(0x22)
#define CPU_OP_LWR	(0x26)
#define CPU_OP_MF	(0x00)
#define CPU_OP_MFHI	(0x10)
#define CPU_OP_MFLO	(0x12)
#define CPU_OP_MT	(0x04)
#define CPU_OP_MTHI	(0x11)
#define CPU_OP_MTLO	(0x13)
#define CPU_OP_MULT	(0x18)
#define CPU_OP_MULTU	(0x19)
#define CPU_OP_MVMVA	(0x12)
#define CPU_OP_NCCS	(0x1B)
#define CPU_OP_NCCT	(0x3F)
#define CPU_OP_NCDS	(0x13)
#define CPU_OP_NCDT	(0x16)
#define CPU_OP_NCLIP	(0x06)
#define CPU_OP_NCS	(0x1E)
#define CPU_OP_NCT	(0x20)
#define CPU_OP_NOR	(0x27)
#define CPU_OP_OP	(0x0C)
#define CPU_OP_OR	(0x25)
#define CPU_OP_ORI	(0x0D)
#define CPU_OP_RFE	(0x10)
#define CPU_OP_RTPS	(0x01)
#define CPU_OP_RTPT	(0x30)
#define CPU_OP_SB	(0x28)
#define CPU_OP_SH	(0x29)
#define CPU_OP_SLL	(0x00)
#define CPU_OP_SLLV	(0x04)
#define CPU_OP_SLT	(0x2A)
#define CPU_OP_SLTI	(0x0A)
#define CPU_OP_SLTIU	(0x0B)
#define CPU_OP_SLTU	(0x2B)
#define CPU_OP_SQR	(0x28)
#define CPU_OP_SRA	(0x03)
#define CPU_OP_SRAV	(0x07)
#define CPU_OP_SRL	(0x02)
#define CPU_OP_SRLV	(0x06)
#define CPU_OP_SUB	(0x22)
#define CPU_OP_SUBU	(0x23)
#define CPU_OP_SW	(0x2B)
#define CPU_OP_SWC2	(0x3A)
#define CPU_OP_SWL	(0x2A)
#define CPU_OP_SWR	(0x2E)
#define CPU_OP_SYSCALL	(0x0C)
#define CPU_OP_XOR	(0x26)
#define CPU_OP_XORI	(0x0E)

#define CPU_GPR_zero	(0)
#define CPU_GPR_at	(1)
#define CPU_GPR_v0	(2)
#define CPU_GPR_v1	(3)
#define CPU_GPR_a0	(4)
#define CPU_GPR_a1	(5)
#define CPU_GPR_a2	(6)
#define CPU_GPR_a3	(7)
#define CPU_GPR_t0	(8)
#define CPU_GPR_t1	(9)
#define CPU_GPR_t2	(10)
#define CPU_GPR_t3	(11)
#define CPU_GPR_t4	(12)
#define CPU_GPR_t5	(13)
#define CPU_GPR_t6	(14)
#define CPU_GPR_t7	(15)
#define CPU_GPR_s0	(16)
#define CPU_GPR_s1	(17)
#define CPU_GPR_s2	(18)
#define CPU_GPR_s3	(19)
#define CPU_GPR_s4	(20)
#define CPU_GPR_s5	(21)
#define CPU_GPR_s6	(22)
#define CPU_GPR_s7	(23)
#define CPU_GPR_t8	(24)
#define CPU_GPR_t9	(25)
#define CPU_GPR_k0	(26)
#define CPU_GPR_k1	(27)
#define CPU_GPR_gp	(28)
#define CPU_GPR_sp	(29)
#define CPU_GPR_fp	(30)
#define CPU_GPR_ra	(31)

#define CPU_CP0_CPR_Index	(0)
#define CPU_CP0_CPR_Random	(1)
#define CPU_CP0_CPR_EntryLo	(2)
#define CPU_CP0_CPR_BPC		(3)
#define CPU_CP0_CPR_Context	(4)
#define CPU_CP0_CPR_BDA		(5)
#define CPU_CP0_CPR_TAR		(6)
#define CPU_CP0_CPR_DCIC	(7)
#define CPU_CP0_CPR_BadA	(8)
#define CPU_CP0_CPR_BDAM	(9)
#define CPU_CP0_CPR_EntryHi	(10)
#define CPU_CP0_CPR_BPCM	(11)
#define CPU_CP0_CPR_SR		(12)
#define CPU_CP0_CPR_Cause	(13)
#define CPU_CP0_CPR_EPC		(14)
#define CPU_CP0_CPR_PRId	(15)

#define CPU_CP2_CPR_VXY0	(0)
#define CPU_CP2_CPR_VZ0		(1)
#define CPU_CP2_CPR_VXY1	(2)
#define CPU_CP2_CPR_VZ1		(3)
#define CPU_CP2_CPR_VXY2	(4)
#define CPU_CP2_CPR_VZ2		(5)
#define CPU_CP2_CPR_RGB		(6)
#define CPU_CP2_CPR_OTZ		(7)
#define CPU_CP2_CPR_IR0		(8)
#define CPU_CP2_CPR_IR1		(9)
#define CPU_CP2_CPR_IR2		(10)
#define CPU_CP2_CPR_IR3		(11)
#define CPU_CP2_CPR_SXY0	(12)
#define CPU_CP2_CPR_SXY1	(13)
#define CPU_CP2_CPR_SXY2	(14)
#define CPU_CP2_CPR_SXYP	(15)
#define CPU_CP2_CPR_SZ0		(16)
#define CPU_CP2_CPR_SZ1		(17)
#define CPU_CP2_CPR_SZ2		(18)
#define CPU_CP2_CPR_SZ3		(19)
#define CPU_CP2_CPR_RGB0	(20)
#define CPU_CP2_CPR_RGB1	(21)
#define CPU_CP2_CPR_RGB2	(22)
#define CPU_CP2_CPR_RES1	(23)
#define CPU_CP2_CPR_MAC0	(24)
#define CPU_CP2_CPR_MAC1	(25)
#define CPU_CP2_CPR_MAC2	(26)
#define CPU_CP2_CPR_MAC3	(27)
#define CPU_CP2_CPR_IRGB	(28)
#define CPU_CP2_CPR_ORGB	(29)
#define CPU_CP2_CPR_LZCS	(30)
#define CPU_CP2_CPR_LZCR	(31)

#define CPU_CP2_CCR_R11R12	(0)
#define CPU_CP2_CCR_R13R21	(1)
#define CPU_CP2_CCR_R22R23	(2)
#define CPU_CP2_CCR_R31R32	(3)
#define CPU_CP2_CCR_R33		(4)
#define CPU_CP2_CCR_TRX		(5)
#define CPU_CP2_CCR_TRY		(6)
#define CPU_CP2_CCR_TRZ		(7)
#define CPU_CP2_CCR_L11L12	(8)
#define CPU_CP2_CCR_L13L21	(9)
#define CPU_CP2_CCR_L22L23	(10)
#define CPU_CP2_CCR_L31L32	(11)
#define CPU_CP2_CCR_L33		(12)
#define CPU_CP2_CCR_RBK		(13)
#define CPU_CP2_CCR_GBK		(14)
#define CPU_CP2_CCR_BBK		(15)
#define CPU_CP2_CCR_LR1LR2	(16)
#define CPU_CP2_CCR_LR3LG1	(17)
#define CPU_CP2_CCR_LG2LG3	(18)
#define CPU_CP2_CCR_LB1LB2	(19)
#define CPU_CP2_CCR_LB3		(20)
#define CPU_CP2_CCR_RFC		(21)
#define CPU_CP2_CCR_GFC		(22)
#define CPU_CP2_CCR_BFC		(23)
#define CPU_CP2_CCR_OFX		(24)
#define CPU_CP2_CCR_OFY		(25)
#define CPU_CP2_CCR_H		(26)
#define CPU_CP2_CCR_DQA		(27)
#define CPU_CP2_CCR_DQB		(28)
#define CPU_CP2_CCR_ZSF3	(29)
#define CPU_CP2_CCR_ZSF4	(30)
#define CPU_CP2_CCR_FLAG	(31)

#define CPU_VEC_RST		(0xBFC00000)

#define CPU_CP0_CPR_REG_SR	(12)
#define CPU_CP0_CPR_REG_SR_IsC	(1 << 16)

// clang-format on

/// @brief Retrieves the 6-bit operation code from an instruction.
/// @param instr The instruction in question.
/// @returns The 6-bit operation code.
ALWAYS_INLINE NODISCARD uint cpu_instr_op_get(const u32 instr)
{
	return instr >> 26;
}

/// @brief Retrieves the 5-bit source register specifier from an instruction.
/// @param instr The instruction in question.
/// @returns The 5-bit source register specifier.
ALWAYS_INLINE NODISCARD uint cpu_instr_rs_get(const u32 instr)
{
	return (instr >> 21) & 0x1F;
}

/// @brief Retrieves the 5-bit target (source/destination register) from an
/// instruction.
/// @param instr The instruction in question.
/// @returns The 5-bit target (source/destination register).
ALWAYS_INLINE NODISCARD uint cpu_instr_rt_get(const u32 instr)
{
	return (instr >> 16) & 0x1F;
}

/// @brief Retrieves the 5-bit destination register specifier from an
/// instruction.
/// @param instr The instruction in question.
/// @returns The 5-bit destination register specifier.
ALWAYS_INLINE NODISCARD uint cpu_instr_rd_get(const u32 instr)
{
	return (instr >> 11) & 0x1F;
}

/// @brief Retrieves the 5-bit shift amount from an instruction.
/// @param instr The instruction in question.
/// @returns The 5-bit shift amount.
ALWAYS_INLINE NODISCARD uint cpu_instr_shamt_get(const u32 instr)
{
	return (instr >> 6) & 0x1F;
}

/// @brief Retrieves the 6-bit function field from an instruction.
/// @param instr The instruction in question.
/// @returns The 6-bit function field.
ALWAYS_INLINE NODISCARD uint cpu_instr_funct_get(const u32 instr)
{
	return instr & 0x3F;
}

/// @brief Retrieves the 26-bit jump target address from an instruction.
/// @param instr The instruction in question.
/// @returns The 26-bit jump target address.
ALWAYS_INLINE NODISCARD uint cpu_instr_target_get(const u32 instr)
{
	return instr & 0x3FFFFFF;
}

/// @brief Retrieves the 16-bit immediate, branch or address displacement from
/// an instruction.
/// @param instr The instruction in question.
/// @returns The 16-bit immediate, branch or address displacement.
ALWAYS_INLINE NODISCARD u16 cpu_instr_imm_get(const u32 instr)
{
	return instr & 0xFFFF;
}

/// @brief Retrieves the zero-extended 16-bit immediate, branch or address
/// displacement from an instruction.
/// @param instr The instruction in question.
/// @returns The zero-extended 16-bit immediate, branch or address displacement.
ALWAYS_INLINE NODISCARD u32 cpu_instr_zext_imm_get(const u32 instr)
{
	return cpu_instr_imm_get(instr);
}

/// @brief Retrieves the sign-extended 16-bit immediate, branch or address
/// displacement from an instruction.
/// @param instr The instruction in question.
/// @returns The sign-extended 16-bit immediate, branch or address displacement.
ALWAYS_INLINE NODISCARD u32 cpu_instr_sext_imm_get(const u32 instr)
{
	return (u32)(s16)cpu_instr_imm_get(instr);
}

/// @brief Retrieves the base register for load/store operations.
/// @param instr The instruction in question.
/// @returns The base register for load/store operations.
/// @note This is just an alias to the "rs" register specifier, but it exists to
/// comply with MIPS conventions.
ALWAYS_INLINE NODISCARD u32 cpu_instr_base_get(const u32 instr)
{
	return cpu_instr_rs_get(instr);
}

/// @brief Retrieves the 16-bit offset for load/store operations.
/// @param instr The instruction in question.
/// @returns The 16-bit offset for load/store operations.
/// @note This is just an alias to the sign-extended immediate, but it exists to
/// comply with MIPS conventions.
ALWAYS_INLINE NODISCARD u32 cpu_instr_offset_get(const u32 instr)
{
	return cpu_instr_sext_imm_get(instr);
}

ALWAYS_INLINE NODISCARD u32 cpu_jmp_tgt_get(const u32 instr, const u32 pc)
{
	return (cpu_instr_target_get(instr) << 2) | (pc & 0xF0000000);
}

ALWAYS_INLINE NODISCARD u32 cpu_branch_tgt_get(const u32 instr, const u32 pc)
{
	return ((cpu_instr_offset_get(instr) << 2) + pc) + sizeof(u32);
}

ALWAYS_INLINE NODISCARD u32 cpu_vaddr_to_paddr(const u32 vaddr)
{
	return vaddr & 0x1FFFFFFF;
}

extern const char *const exc_code_names[];

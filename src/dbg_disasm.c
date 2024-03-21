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

#include "psycho/cpu_defs.h"
#include "psycho/dbg_disasm.h"
#include "cpu_defs.h"

// clang-format off
#define zero	(CPU_GPR_zero)
#define at	(CPU_GPR_at)
#define v0	(CPU_GPR_v0)
#define v1	(CPU_GPR_v1)
#define a0	(CPU_GPR_a0)
#define a1	(CPU_GPR_a1)
#define a2	(CPU_GPR_a2)
#define a3	(CPU_GPR_a3)
#define t0	(CPU_GPR_t0)
#define t1	(CPU_GPR_t1)
#define t2	(CPU_GPR_t2)
#define t3	(CPU_GPR_t3)
#define t4	(CPU_GPR_t4)
#define t5	(CPU_GPR_t5)
#define t6	(CPU_GPR_t6)
#define t7	(CPU_GPR_t7)
#define s0	(CPU_GPR_s0)
#define s1	(CPU_GPR_s1)
#define s2	(CPU_GPR_s2)
#define s3	(CPU_GPR_s3)
#define s4	(CPU_GPR_s4)
#define s5	(CPU_GPR_s5)
#define s6	(CPU_GPR_s6)
#define s7	(CPU_GPR_s7)
#define t8	(CPU_GPR_t8)
#define t9	(CPU_GPR_t9)
#define k0	(CPU_GPR_k0)
#define k1	(CPU_GPR_k1)
#define gp	(CPU_GPR_gp)
#define sp	(CPU_GPR_sp)
#define fp	(CPU_GPR_fp)
#define ra	(CPU_GPR_ra)

#define Index		(CPU_CP0_CPR_Index)
#define Random		(CPU_CP0_CPR_Random)
#define EntryLo		(CPU_CP0_CPR_EntryLo)
#define BPC		(CPU_CP0_CPR_BPC)
#define Context		(CPU_CP0_CPR_Context)
#define BDA		(CPU_CP0_CPR_BDA)
#define TAR		(CPU_CP0_CPR_TAR)
#define DCIC		(CPU_CP0_CPR_DCIC)
#define BadA		(CPU_CP0_CPR_BadA)
#define BDAM		(CPU_CP0_CPR_BDAM)
#define EntryHi		(CPU_CP0_CPR_EntryHi)
#define BPCM		(CPU_CP0_CPR_BPCM)
#define SR		(CPU_CP0_CPR_SR)
#define Cause		(CPU_CP0_CPR_Cause)
#define EPC		(CPU_CP0_CPR_EPC)
#define PRId		(CPU_CP0_CPR_PRId)

#define VXY0	(CPU_CP2_CPR_VXY0)
#define VZ0	(CPU_CP2_CPR_VZ0)
#define VXY1	(CPU_CP2_CPR_VXY1)
#define VZ1	(CPU_CP2_CPR_VZ1)
#define VXY2	(CPU_CP2_CPR_VXY2)
#define VZ2	(CPU_CP2_CPR_VZ2)
#define RGB	(CPU_CP2_CPR_RGB)
#define OTZ	(CPU_CP2_CPR_OTZ)
#define IR0	(CPU_CP2_CPR_IR0)
#define IR1	(CPU_CP2_CPR_IR1)
#define IR2	(CPU_CP2_CPR_IR2)
#define IR3	(CPU_CP2_CPR_IR3)
#define SXY0	(CPU_CP2_CPR_SXY0)
#define SXY1	(CPU_CP2_CPR_SXY1)
#define SXY2	(CPU_CP2_CPR_SXY2)
#define SXYP	(CPU_CP2_CPR_SXYP)
#define SZ0	(CPU_CP2_CPR_SZ0)
#define SZ1	(CPU_CP2_CPR_SZ1)
#define SZ2	(CPU_CP2_CPR_SZ2)
#define SZ3	(CPU_CP2_CPR_SZ3)
#define RGB0	(CPU_CP2_CPR_RGB0)
#define RGB1	(CPU_CP2_CPR_RGB1)
#define RGB2	(CPU_CP2_CPR_RGB2)
#define RES1	(CPU_CP2_CPR_RES1)
#define MAC0	(CPU_CP2_CPR_MAC0)
#define MAC1	(CPU_CP2_CPR_MAC1)
#define MAC2	(CPU_CP2_CPR_MAC2)
#define MAC3	(CPU_CP2_CPR_MAC3)
#define IRGB	(CPU_CP2_CPR_IRGB)
#define ORGB	(CPU_CP2_CPR_ORGB)
#define LZCS	(CPU_CP2_CPR_LZCS)
#define LZCR	(CPU_CP2_CPR_LZCR)

#define R11R12	(CPU_CP2_CCR_R11R12)
#define R13R21	(CPU_CP2_CCR_R13R21)
#define R22R23	(CPU_CP2_CCR_R22R23)
#define R31R32	(CPU_CP2_CCR_R31R32)
#define R33	(CPU_CP2_CCR_R33)
#define TRX	(CPU_CP2_CCR_TRX)
#define TRY	(CPU_CP2_CCR_TRY)
#define TRZ	(CPU_CP2_CCR_TRZ)
#define L11L12	(CPU_CP2_CCR_L11L12)
#define L13L21	(CPU_CP2_CCR_L13L21)
#define L22L23	(CPU_CP2_CCR_L22L23)
#define L31L32	(CPU_CP2_CCR_L31L32)
#define L33	(CPU_CP2_CCR_L33)
#define RBK	(CPU_CP2_CCR_RBK)
#define GBK	(CPU_CP2_CCR_GBK)
#define BBK	(CPU_CP2_CCR_BBK)
#define LR1LR2	(CPU_CP2_CCR_LR1LR2)
#define LR3LG1	(CPU_CP2_CCR_LR3LG1)
#define LG2LG3	(CPU_CP2_CCR_LG2LG3)
#define LB1LB2	(CPU_CP2_CCR_LB1LB2)
#define LB3	(CPU_CP2_CCR_LB3)
#define RFC	(CPU_CP2_CCR_RFC)
#define GFC	(CPU_CP2_CCR_GFC)
#define BFC	(CPU_CP2_CCR_BFC)
#define OFX	(CPU_CP2_CCR_OFX)
#define OFY	(CPU_CP2_CCR_OFY)
#define H	(CPU_CP2_CCR_H)
#define DQA	(CPU_CP2_CCR_DQA)
#define DQB	(CPU_CP2_CCR_DQB)
#define ZSF3	(CPU_CP2_CCR_ZSF3)
#define ZSF4	(CPU_CP2_CCR_ZSF4)
#define FLAG	(CPU_CP2_CCR_FLAG)

const char *const psycho_cpu_gpr_names[PSYCHO_CPU_GPR_REGS_NUM] = {
	[zero] = "zero", [at] = "at", [v0] = "v0", [v1] = "v1", [a0] = "a0",
	[a1]   = "a1",	 [a2] = "a2", [a3] = "a3", [t0] = "t0", [t1] = "t1",
	[t2]   = "t2",	 [t3] = "t3", [t4] = "t4", [t5] = "t5", [t6] = "t6",
	[t7]   = "t7",	 [s0] = "s0", [s1] = "s1", [s2] = "s2", [s3] = "s3",
	[s4]   = "s4",	 [s5] = "s5", [s6] = "s6", [s7] = "s7", [t8] = "t8",
	[t9]   = "t9",	 [k0] = "k0", [k1] = "k1", [gp] = "gp", [sp] = "sp",
	[fp]   = "fp",	 [ra] = "ra"
};

const char *const psycho_cpu_cp0_cpr_names[PSYCHO_CPU_CP0_CPR_REGS_NUM] = {
	[Index]   = "C0_Index",	  [Random] = "C0_Random",
	[EntryLo] = "C0_EntryLo", [BPC]    = "C0_BPC",
	[Context] = "C0_Context", [BDA]	   = "C0_BDA",
	[TAR] 	  = "C0_TAR",	  [DCIC]   = "C0_DCIC",
	[BadA]	  = "C0_BadA",	  [BDAM]   = "C0_BDAM",
	[EntryHi] = "C0_EntryHi", [BPCM]   = "C0_BPCM",
	[SR]	  = "C0_SR",	  [Cause]  = "C0_Cause",
	[EPC]	  = "C0_EPC",	  [PRId]   = "C0_PRId",
	[16]	  = "C0_REG16",	  [17]	   = "C0_REG17",
	[18]	  = "C0_REG18",	  [19] 	   = "C0_REG19",
	[20]	  = "C0_REG20",	  [21]	   = "C0_REG21",
	[22]	  = "C0_REG22",	  [23]	   = "C0_REG23",
	[24]	  = "C0_REG24",	  [25]	   = "C0_REG25",
	[26]	  = "C0_REG26",	  [27]	   = "C0_REG27",
	[28]	  = "C0_REG28",	  [29]	   = "C0_REG29",
	[30]	  = "C0_REG30",	  [31]	   = "C0_REG31"
};

const char *const psycho_cpu_cp2_cpr_names[PSYCHO_CPU_CP2_CPR_REGS_NUM] = {
	[VXY0] = "C2_VXY0", [VZ0]  = "C2_VZ0",	[VXY1] = "C2_VXY1",
	[VZ1]  = "C2_VZ1",  [VXY2] = "C2_VXY2", [VZ2]  = "C2_VZ2",
	[RGB]  = "C2_RGB",  [OTZ]  = "C2_OTZ",	[IR0]  = "C2_IR0",
	[IR1]  = "C2_IR1",  [IR2]  = "C2_IR2",	[IR3]  = "C2_IR3",
	[SXY0] = "C2_SXY0", [SXY1] = "C2_SXY1", [SXY2] = "C2_SYX2",
	[SXYP] = "C2_SXYP", [SZ0]  = "C2_SZ0",	[SZ1]  = "C2_SZ1",
	[SZ2]  = "C2_SZ2",  [SZ3]  = "C2_SZ3",	[RGB0] = "C2_RGB0",
	[RGB1] = "C2_RGB1", [RGB2] = "C2_RGB2", [RES1] = "C2_RES1",
	[MAC0] = "C2_MAC0", [MAC1] = "C2_MAC1", [MAC2] = "C2_MAC2",
	[MAC3] = "C2_MAC3", [IRGB] = "C2_IRGB", [ORGB] = "C2_ORGB",
	[LZCS] = "C2_LZCS", [LZCR] = "C2_LZCR"
};

const char *const psycho_cpu_cp2_ccr_names[PSYCHO_CPU_CP2_CCR_REGS_NUM] = {
	[R11R12] = "C2_R11R12", [R13R21] = "C2_R13R21", [R22R23] = "C2_R22R23",
	[R31R32] = "C2_R31R23", [R33] 	 = "C2_R33",	[TRX] 	 = "C2_TRX",
	[TRY] 	 = "C2_TRY",	[TRZ] 	 = "C2_TRZ",	[L11L12] = "C2_L11L12",
	[L13L21] = "C2_L13L21", [L22L23] = "C2_L22L23", [L31L32] = "C2_L31L32",
	[L33] 	 = "C2_L33",	[RBK] 	 = "C2_RBK",	[GBK] 	 = "C2_GBK",
	[BBK] 	 = "C2_BBK",	[LR1LR2] = "C2_LR1LR2", [LR3LG1] = "C2_LR3LG1",
	[LG2LG3] = "C2_LG2LG3", [LB1LB2] = "C2_LB1LB2", [LB3] 	 = "C2_LB3",
	[RFC] 	 = "C2_RFC",	[GFC] 	 = "C2_GFC",	[BFC] 	 = "C2_BFC",
	[OFX] 	 = "C2_OFX",	[OFY] 	 = "C2_OFY",	[H] 	 = "C2_H",
	[DQA] 	 = "C2_DQA",	[DQB] 	 = "C2_DQB",	[ZSF3] 	 = "C2_ZSF3",
	[ZSF4] 	 = "C2_ZSF4",	[FLAG] 	 = "C2_FLAG"
};
// clang-format on

void psycho_dbg_disasm(struct psycho_ctx *const ctx, const u32 instr,
		       const u32 pc)
{
}

void psycho_dbg_disasm_trace(struct psycho_ctx *const ctx)
{
}

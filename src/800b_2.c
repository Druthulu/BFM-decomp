#include "common.h"

INCLUDE_ASM("asm/nonmatchings/800b_2", LightColor);

INCLUDE_ASM("asm/nonmatchings/800b_2", DpqColorLight);

INCLUDE_ASM("asm/nonmatchings/800b_2", DpqColor3);

INCLUDE_ASM("asm/nonmatchings/800b_2", Intpl);

INCLUDE_ASM("asm/nonmatchings/800b_2", Square12);

INCLUDE_ASM("asm/nonmatchings/800b_2", Square0);

INCLUDE_ASM("asm/nonmatchings/800b_2", AverageZ3);

__asm__(".text\n.align 2\n.globl AverageZ4\n.ent\tAverageZ4\n"
"AverageZ4:\n.frame $sp,0,$31\n.mask 0x00000000,0\n.fmask 0,0\n"
".set\tnoreorder\n"
"mtc2 $a0, $16\n"
"mtc2 $a1, $17\n"
"mtc2 $a2, $18\n"
"mtc2 $a3, $19\n"
"nop\n"
"avsz4\n"
"mfc2 $v0, $7\n"
"jr $ra\n"
"nop\n"
".set\treorder\n.end\tAverageZ4\n");

INCLUDE_ASM("asm/nonmatchings/800b_2", OuterProduct12);

INCLUDE_ASM("asm/nonmatchings/800b_2", OuterProduct0);

INCLUDE_ASM("asm/nonmatchings/800b_2", func_80049440);

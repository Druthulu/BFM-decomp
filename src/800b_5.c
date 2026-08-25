#include "common.h"

INCLUDE_ASM("asm/nonmatchings/800b_5", func_8004978C);

INCLUDE_ASM("asm/nonmatchings/800b_5", FGO_01_OBJ_64);

INCLUDE_ASM("asm/nonmatchings/800b_5", FGO_01_OBJ_CC);

INCLUDE_ASM("asm/nonmatchings/800b_5", FGO_01_OBJ_160);

INCLUDE_ASM("asm/nonmatchings/800b_5", RotMatrixYXZ);

INCLUDE_ASM("asm/nonmatchings/800b_5", FGO_02_OBJ_68);

INCLUDE_ASM("asm/nonmatchings/800b_5", FGO_02_OBJ_CC);

INCLUDE_ASM("asm/nonmatchings/800b_5", FGO_02_OBJ_160);

INCLUDE_ASM("asm/nonmatchings/800b_5", func_80049CAC);

INCLUDE_ASM("asm/nonmatchings/800b_5", FGO_03_OBJ_64);

INCLUDE_ASM("asm/nonmatchings/800b_5", FGO_03_OBJ_CC);

INCLUDE_ASM("asm/nonmatchings/800b_5", FGO_03_OBJ_160);

INCLUDE_ASM("asm/nonmatchings/800b_5", RotMatrixX);

INCLUDE_ASM("asm/nonmatchings/800b_5", FGO_04_OBJ_64);

INCLUDE_ASM("asm/nonmatchings/800b_5", RotMatrixY);

__asm__(".text\n.align 2\n.globl FGO_05_OBJ_64\n.ent\tFGO_05_OBJ_64\n"
        "FGO_05_OBJ_64:\n.frame $sp,0,$31\n"
        ".set\tnoreorder\n"
        "lh $t2, 0($a1)\n"
        "lh $t5, 12($a1)\n"
        "multu $t0, $t2\n"
        "lh $t3, 2($a1)\n"
        "lh $t6, 14($a1)\n"
        "mflo $t8\n"
        "lh $t4, 4($a1)\n"
        "lh $t7, 16($a1)\n"
        "multu $t1, $t5\n"
        "nop\n"
        "nop\n"
        "mflo $t9\n"
        "subu $t9, $t8, $t9\n"
        "sra $t8, $t9, 12\n"
        "multu $t0, $t3\n"
        "sh $t8, 0($a1)\n"
        "nop\n"
        "mflo $t8\n"
        "nop\n"
        "nop\n"
        "multu $t1, $t6\n"
        "nop\n"
        "nop\n"
        "mflo $t9\n"
        "subu $t9, $t8, $t9\n"
        "sra $t8, $t9, 12\n"
        "multu $t0, $t4\n"
        "sh $t8, 2($a1)\n"
        "nop\n"
        "mflo $t8\n"
        "nop\n"
        "nop\n"
        "multu $t1, $t7\n"
        "nop\n"
        "nop\n"
        "mflo $t9\n"
        "subu $t9, $t8, $t9\n"
        "sra $t8, $t9, 12\n"
        "multu $t1, $t2\n"
        "sh $t8, 4($a1)\n"
        "nop\n"
        "mflo $t8\n"
        "nop\n"
        "nop\n"
        "multu $t0, $t5\n"
        "nop\n"
        "nop\n"
        "mflo $t9\n"
        "addu $t9, $t8, $t9\n"
        "sra $t8, $t9, 12\n"
        "multu $t1, $t3\n"
        "sh $t8, 12($a1)\n"
        "nop\n"
        "mflo $t8\n"
        "nop\n"
        "nop\n"
        "multu $t0, $t6\n"
        "nop\n"
        "nop\n"
        "mflo $t9\n"
        "addu $t9, $t8, $t9\n"
        "sra $t8, $t9, 12\n"
        "multu $t1, $t4\n"
        "sh $t8, 14($a1)\n"
        "nop\n"
        "mflo $t8\n"
        "nop\n"
        "nop\n"
        "multu $t0, $t7\n"
        "nop\n"
        "nop\n"
        "mflo $t9\n"
        "addu $t9, $t8, $t9\n"
        "sra $t8, $t9, 12\n"
        "sh $t8, 16($a1)\n"
        "jr $ra\n"
        "nop\n"
        ".set\treorder\n.end\tFGO_05_OBJ_64\n");
__asm__(".word 0");
__asm__(".word 0");

INCLUDE_ASM("asm/nonmatchings/800b_5", RotMatrixZ);

__asm__(".text\n.align 2\n.globl FGO_06_OBJ_64\n.ent\tFGO_06_OBJ_64\n"
        "FGO_06_OBJ_64:\n.frame $sp,0,$31\n"
        ".set\tnoreorder\n"
        "lh $t2, 0($a1)\n"
        "lh $t5, 6($a1)\n"
        "multu $t0, $t2\n"
        "lh $t3, 2($a1)\n"
        "lh $t6, 8($a1)\n"
        "mflo $t8\n"
        "lh $t4, 4($a1)\n"
        "lh $t7, 10($a1)\n"
        "multu $t1, $t5\n"
        "nop\n"
        "nop\n"
        "mflo $t9\n"
        "subu $t9, $t8, $t9\n"
        "sra $t8, $t9, 12\n"
        "multu $t0, $t3\n"
        "sh $t8, 0($a1)\n"
        "nop\n"
        "mflo $t8\n"
        "nop\n"
        "nop\n"
        "multu $t1, $t6\n"
        "nop\n"
        "nop\n"
        "mflo $t9\n"
        "subu $t9, $t8, $t9\n"
        "sra $t8, $t9, 12\n"
        "multu $t0, $t4\n"
        "sh $t8, 2($a1)\n"
        "nop\n"
        "mflo $t8\n"
        "nop\n"
        "nop\n"
        "multu $t1, $t7\n"
        "nop\n"
        "nop\n"
        "mflo $t9\n"
        "subu $t9, $t8, $t9\n"
        "sra $t8, $t9, 12\n"
        "multu $t1, $t2\n"
        "sh $t8, 4($a1)\n"
        "nop\n"
        "mflo $t8\n"
        "nop\n"
        "nop\n"
        "multu $t0, $t5\n"
        "nop\n"
        "nop\n"
        "mflo $t9\n"
        "addu $t9, $t8, $t9\n"
        "sra $t8, $t9, 12\n"
        "multu $t1, $t3\n"
        "sh $t8, 6($a1)\n"
        "nop\n"
        "mflo $t8\n"
        "nop\n"
        "nop\n"
        "multu $t0, $t6\n"
        "nop\n"
        "nop\n"
        "mflo $t9\n"
        "addu $t9, $t8, $t9\n"
        "sra $t8, $t9, 12\n"
        "multu $t1, $t4\n"
        "sh $t8, 8($a1)\n"
        "nop\n"
        "mflo $t8\n"
        "nop\n"
        "nop\n"
        "multu $t0, $t7\n"
        "nop\n"
        "nop\n"
        "mflo $t9\n"
        "addu $t9, $t8, $t9\n"
        "sra $t8, $t9, 12\n"
        "sh $t8, 10($a1)\n"
        "jr $ra\n"
        "nop\n"
        ".set\treorder\n.end\tFGO_06_OBJ_64\n");
__asm__(".word 0");
__asm__(".word 0");

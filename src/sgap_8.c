#include "common.h"

INCLUDE_ASM("asm/nonmatchings/sgap_8", _SsVmKeyOnNow);

INCLUDE_ASM("asm/nonmatchings/sgap_8", VM_NOWON_OBJ_1C0);

INCLUDE_ASM("asm/nonmatchings/sgap_8", VM_NOWON_OBJ_230);

INCLUDE_ASM("asm/nonmatchings/sgap_8", VM_NOWON_OBJ_2A0);

INCLUDE_ASM("asm/nonmatchings/sgap_8", VM_NOWON_OBJ_2C8);

__asm__(".text\n.align 2\n.globl VM_NOWON_OBJ_3D4\n.ent VM_NOWON_OBJ_3D4\n"
        "VM_NOWON_OBJ_3D4:\n"
        ".frame $sp,16,$31\n.mask 0,0\n.fmask 0,0\n.set noreorder\n"
        "lui $v0, %hi(D_800B9B34)\n"
        "lbu $v0, %lo(D_800B9B34)($v0)\n"
        "nop\n"
        "andi $v0, $v0, 4\n"
        "beqz $v0, .L80040D54\n"
        "nor $v1, $zero, $a2\n"
        "lui $v0, %hi(D_80078D90)\n"
        "lhu $v0, %lo(D_80078D90)($v0)\n"
        "lui $v1, %hi(D_80078D92)\n"
        "lhu $v1, %lo(D_80078D92)($v1)\n"
        "or $v0, $v0, $a2\n"
        "or $v1, $v1, $a1\n"
        "lui $at, %hi(D_80078D90)\n"
        "sh $v0, %lo(D_80078D90)($at)\n"
        "lui $at, %hi(D_80078D92)\n"
        "sh $v1, %lo(D_80078D92)($at)\n"
        "j VM_NOWON_OBJ_44C\n"
        ".L80040D54:\n"
        "lui $v0, %hi(D_80078D90)\n"
        "lhu $v0, %lo(D_80078D90)($v0)\n"
        "nop\n"
        "and $v0, $v0, $v1\n"
        "lui $at, %hi(D_80078D90)\n"
        "sh $v0, %lo(D_80078D90)($at)\n"
        "lui $v0, %hi(D_80078D92)\n"
        "lhu $v0, %lo(D_80078D92)($v0)\n"
        "nor $v1, $zero, $a1\n"
        "and $v0, $v0, $v1\n"
        "lui $at, %hi(D_80078D92)\n"
        "sh $v0, %lo(D_80078D92)($at)\n"
        ".set reorder\n.end VM_NOWON_OBJ_3D4\n");

INCLUDE_ASM("asm/nonmatchings/sgap_8", VM_NOWON_OBJ_44C);

INCLUDE_ASM("asm/nonmatchings/sgap_8", func_80040DE8);

INCLUDE_ASM("asm/nonmatchings/sgap_8", func_80041354);

INCLUDE_ASM("asm/nonmatchings/sgap_8", func_800413B8);

INCLUDE_ASM("asm/nonmatchings/sgap_8", func_80041400);

INCLUDE_ASM("asm/nonmatchings/sgap_8", func_80041448);

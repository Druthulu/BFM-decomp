#include "common.h"

extern void func_80053CF8(void);
extern void func_80052D00(void);
extern void func_80052BEC(void);
extern s16 D_800C7C74;

void func_800525DC(u16 w, u16 h, u16 intmode, u16 dither, u16 varh)
{
    func_80052654(w, h, intmode, dither, varh);
    func_80053CF8();
    D_800C7C74 = 0;
    func_8005283C(w, h);
    func_80052D00();
    func_80052BEC();
}


extern void func_80059234(s32 a0);
extern void func_80059D68(u8 *a0);
extern s32 func_80043078(void);
extern void func_80059FC0(u8 *a0);

extern s16 D_800A6440;
extern s16 D_800A6442;
extern s16 D_800A6444;
extern s16 D_800A6446;
extern s16 D_800A6448;
extern s16 D_800A644A;
extern s16 D_800A644C;
extern u8 D_800A644E;
extern u8 D_800A644F;
extern u8 D_800A6450;

extern s16 D_800A6498;
extern s16 D_800A649A;
extern s16 D_800A649C;
extern s16 D_800A649E;
extern s16 D_800A64A0;
extern s16 D_800A64A2;
extern s16 D_800A64A4;
extern s16 D_800A64A6;

extern u8 D_800A64A8;
extern u8 D_800A64A9;
extern u8 D_800A64AA;

extern s16 D_800C7C88;

void func_80052654(u16 w, u16 h, u16 intmode, u16 dither, u16 varh)
{
    s16 *p;
    s16 *q;

    func_80059234((((intmode >> 4) & 3) == 3) ? 3 : 0);

    p = &D_800A6440;
    D_800A6442 = 0;
    *p = 0;
    D_800A644A = 0;
    D_800A6448 = 0;
    D_800A6446 = 0;
    D_800A6444 = 0;
    D_800A644C = 0;
    D_800A644E = dither;
    D_800A644F = 0;
    D_800A6450 = 0;

    func_80059D68((u8 *)p - 8);

    q = &D_800A6498;
    *q = 0;
    D_800A649A = 0;
    D_800A649C = w;
    D_800A649E = h;
    D_800A64A0 = 0;
    D_800A64A2 = 0;
    D_800A64A4 = 0;
    D_800A64A6 = 0;

    if (func_80043078() == 1) {
        D_800A64A2 = 0x18;
        D_800A64AA = 1;
    }

    D_800A64A8 = intmode & 1;
    D_800C7C88 = intmode & 4;
    D_800A64A9 = varh;

    func_80059FC0((u8 *)q);
}

INCLUDE_ASM("asm/nonmatchings/gsgap3", GsInitGraph2);


typedef struct {
    s16 m[3][3];
    s32 t[3];
} Mtx32;

extern volatile s32 D_800AE618;
extern volatile s32 D_800AE61C;
extern Mtx32 D_800AE620;
extern Mtx32 D_800AE7F0;
extern Mtx32 D_800A63F0;
extern Mtx32 D_800A6558;
extern s16 D_800A4F3C;
extern s16 D_800A4F3E;
extern s16 D_800A4F40;
extern s16 D_800A4F42;
extern s16 D_800A5E50;
extern s16 D_800A5E52;
extern s16 D_800AE820;
extern s16 D_800AE822;
extern s16 D_800AE824;
extern s16 D_800AE826;
extern u8 D_80078813;
extern u8 D_80078817;
extern u8 D_80078823;
extern u8 D_80078827;
extern s32 D_800C7C70;

void func_8005283C(s32 arg0, s32 arg1) {
    s32 h;
    s32 w;
    s32 q;

    D_800AE61C = (u16)arg1;
    h = D_800AE61C;
    D_800AE618 = (u16)arg0;
    w = D_800AE618;
    q = (h << 14) / w;

    D_800AE620.m[0][2] = 0;
    D_800AE620.m[0][1] = 0;
    D_800AE620.m[1][2] = 0;
    D_800AE620.m[1][0] = 0;
    D_800AE620.m[2][1] = 0;
    D_800AE620.m[2][0] = 0;
    D_800AE620.t[2] = 0;
    D_800AE620.t[1] = 0;
    D_800AE620.t[0] = 0;
    D_800AE620.m[0][0] = 0x1000;
    D_800AE620.m[1][1] = 0x1000;
    D_800AE620.m[2][2] = 0x1000;

    D_800AE7F0 = D_800AE620;
    D_800A63F0 = D_800AE620;
    D_800A63F0.m[2][2] = 0;
    D_800A63F0.m[1][1] = 0;
    D_800A63F0.m[0][0] = 0;
    D_800A6558 = D_800A63F0;

    D_800A4F3C = 0;
    D_800A4F3E = 0;
    D_800A4F40 = 0;
    D_800A4F42 = 0;
    D_800A5E52 = 0;
    D_800A5E50 = 0;
    D_800AE822 = 0;
    D_800AE7F0.m[1][1] = q / 3;
    D_800AE820 = 0;
    D_800AE824 = w;
    D_800AE826 = h;
    D_80078813 = 3;
    D_80078817 = 2;
    D_80078823 = 3;
    D_80078827 = 2;
    D_800C7C70 = 1;
}


/*
 * GsSortClear -- writes the clear-color bytes (r,g,b) plus the width/height/z fields of the
 * current double-buffer's sort-tile entry (a 16-byte-stride record based at D_80078810, whose
 * individual fields never got a struct symbol -- each is its own splat-auto D_######## label,
 * per this TU's convention of one symbol per referenced address). Like func_80059FC0 /
 * SYS_OBJ_E34 (src/800c.c) and GsTMDfastG3GL (src/800b2.c), BOTH branches end with a raw,
 * unlinked tail jump: the taken (if D_800A64A9) branch ends "j GS_001_OBJ_5D0" (args left live
 * in $a1==idx*16, $a3 untouched from our own caller); the not-taken branch has NO jump and NO
 * "jr $ra" at all -- it falls straight through into GS_001_OBJ_5D0's own code, which owns the
 * shared epilogue (lw $ra,0x10($sp); addiu $sp,$sp,0x18; jr $ra) for this frame. gcc-2.7.2 has
 * no sibcall / cross-function tail-merge pass (matching-cookbook.md §179-C) and unconditionally
 * appends its own return sequence to any ordinary C function body, so this can only be written
 * as FILE-SCOPE __asm__ -- opaque text the compiler never runs expand_function_end over.
 */
__asm__(
    ".text\n"
    ".align\t2\n"
    ".globl\tGsSortClear\n"
    ".ent\tGsSortClear\n"
    "GsSortClear:\n"
    ".frame\t$sp,24,$31\n"
    ".mask\t0x80000000,-8\n"
    ".fmask\t0x00000000,0\n"
    ".set\tnoreorder\n"
    "lui   $2, %hi(D_800C7C74)\n"
    "lh    $2, %lo(D_800C7C74)($2)\n"
    "addiu $sp, $sp, -24\n"
    "sw    $31, 16($sp)\n"
    "sll   $2, $2, 4\n"
    "lui   $1, %hi(D_80078814)\n"
    "addu  $1, $1, $2\n"
    "sb    $4, %lo(D_80078814)($1)\n"
    "lui   $2, %hi(D_800C7C74)\n"
    "lh    $2, %lo(D_800C7C74)($2)\n"
    "nop\n"
    "sll   $2, $2, 4\n"
    "lui   $1, %hi(D_80078815)\n"
    "addu  $1, $1, $2\n"
    "sb    $5, %lo(D_80078815)($1)\n"
    "lui   $2, %hi(D_800C7C74)\n"
    "lh    $2, %lo(D_800C7C74)($2)\n"
    "nop\n"
    "sll   $2, $2, 4\n"
    "lui   $1, %hi(D_80078816)\n"
    "addu  $1, $1, $2\n"
    "sb    $6, %lo(D_80078816)($1)\n"
    "lui   $2, %hi(D_800C7C74)\n"
    "lh    $2, %lo(D_800C7C74)($2)\n"
    "nop\n"
    "sll   $4, $2, 1\n"
    "sll   $5, $2, 4\n"
    "lui   $1, %hi(D_800794E0)\n"
    "addu  $1, $1, $4\n"
    "lhu   $3, %lo(D_800794E0)($1)\n"
    "lui   $2, %hi(D_800AE61C)\n"
    "lw    $2, %lo(D_800AE61C)($2)\n"
    "lui   $1, %hi(D_80078818)\n"
    "addu  $1, $1, $5\n"
    "sh    $3, %lo(D_80078818)($1)\n"
    "lui   $1, %hi(D_800794E4)\n"
    "addu  $1, $1, $4\n"
    "lhu   $3, %lo(D_800794E4)($1)\n"
    "lui   $1, %hi(D_8007881E)\n"
    "addu  $1, $1, $5\n"
    "sh    $2, %lo(D_8007881E)($1)\n"
    "lui   $1, %hi(D_8007881A)\n"
    "addu  $1, $1, $5\n"
    "sh    $3, %lo(D_8007881A)($1)\n"
    "lui   $2, %hi(D_800A64A9)\n"
    "lbu   $2, %lo(D_800A64A9)($2)\n"
    "nop\n"
    "beqz  $2, 1f\n"
    " nop\n"
    "lui   $2, %hi(D_800AE618)\n"
    "lw    $2, %lo(D_800AE618)($2)\n"
    "nop\n"
    "sll   $3, $2, 1\n"
    "addu  $3, $3, $2\n"
    "srl   $2, $3, 31\n"
    "addu  $3, $3, $2\n"
    "sra   $3, $3, 1\n"
    "lui   $1, %hi(D_8007881C)\n"
    "addu  $1, $1, $5\n"
    "sh    $3, %lo(D_8007881C)($1)\n"
    "j     GS_001_OBJ_5D0\n"
    " nop\n"
    "1:\n"
    "lui   $2, %hi(D_800AE618)\n"
    "lw    $2, %lo(D_800AE618)($2)\n"
    "lui   $1, %hi(D_8007881C)\n"
    "addu  $1, $1, $5\n"
    "sh    $2, %lo(D_8007881C)($1)\n"
    ".set\treorder\n"
    ".end\tGsSortClear\n"
);

INCLUDE_ASM("asm/nonmatchings/gsgap3", GS_001_OBJ_5D0);

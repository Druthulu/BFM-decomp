#include "common.h"


/* GsSortBg (asm/nonmatchings/800b_7/GsSortBg.s, 0x1B4 = 109 ins).
 *
 * This chunk has NO epilogue: it ends on "jal gte_scale_matrix" + delay slot and
 * simply falls through into the next symbol, gfx2D_BG0_OBJ_1B4 (0x800509C0), which
 * has no prologue either -- it consumes $s5/$fp/$s1 and stack slots set up here.
 * GsSortBg also exits mid-body with a bare "j gfx2D_BG0_OBJ_1B4". gcc-2.7.2 cannot
 * express this from C: expand_function_end/function_epilogue unconditionally append
 * "jr $ra; nop" to any cc1-compiled function (no sibcall, no tail-merge pass), and
 * neither noreturn nor __builtin_unreachable suppresses it. Matching-cookbook
 * SS179-C: emit the whole function as FILE-SCOPE basic __asm__, transcribed 1:1,
 * with literal tab-formed ".ent\t"/".end\t" text (maspsx special-cases lines
 * starting with ".ent\t" to emit a fresh ".set\tnoreorder"; a plain ".set" line is
 * swallowed, and using the .s macros glabel/endlabel would leave GNU as in default
 * REORDER mode, auto-inserting nops after every branch and displacing our
 * hand-filled delay slots). Memory displacements are written in DECIMAL because
 * maspsx parses load/store offsets with base-10 int() before its range check.
 * Branch targets .L80051010 (defined in gfx2D_BG0_OBJ_698.s, included later in
 * this same translation unit) and the cross-TU callees resolve at assembly/link
 * time exactly as the target's own relocation lines name them.
 */
__asm__(
    ".text\n"
    ".align\t2\n"
    ".globl\tGsSortBg\n"
    ".ent\tGsSortBg\n"
    "GsSortBg:\n"
        ".set\tnoreorder\n"
        "addiu $sp, $sp, -224\n"
        "sw    $s5, 204($sp)\n"
        "addu  $s5, $a0, $zero\n"
        "sw    $ra, 220($sp)\n"
        "sw    $fp, 216($sp)\n"
        "sw    $s7, 212($sp)\n"
        "sw    $s6, 208($sp)\n"
        "sw    $s4, 200($sp)\n"
        "sw    $s3, 196($sp)\n"
        "sw    $s2, 192($sp)\n"
        "sw    $s1, 188($sp)\n"
        "sw    $s0, 184($sp)\n"
        "sw    $a1, 80($sp)\n"
        "lw    $a1, 0($s5)\n"
        "nop\n"
        "bltz  $a1, .L80051010\n"
        "sh    $a2, 88($sp)\n"
        "lw    $v0, 20($s5)\n"
        "nop\n"
        "lhu   $a2, 2($v0)\n"
        "nop\n"
        "andi  $a0, $a2, 0xFFFF\n"
        "beqz  $a0, .L80051010\n"
        "nop\n"
        "lhu   $a3, 4($v0)\n"
        "nop\n"
        "beqz  $a3, .L80051010\n"
        "nop\n"
        "lbu   $t8, 0($v0)\n"
        "nop\n"
        "bnez  $t8, .L80050894\n"
        "sh    $t8, 128($sp)\n"
        "addiu $t8, $zero, 256\n"
        "sh    $t8, 128($sp)\n"
        ".L80050894:\n"
        "lbu   $fp, 1($v0)\n"
        "nop\n"
        "bnez  $fp, .L800508A8\n"
        "nop\n"
        "addiu $fp, $zero, 256\n"
        ".L800508A8:\n"
        "lhu   $t8, 128($sp)\n"
        "nop\n"
        "mult  $t8, $a0\n"
        "srl   $v1, $a1, 29\n"
        "andi  $v1, $v1, 0x2\n"
        "srl   $v0, $a1, 6\n"
        "andi  $v0, $v0, 0x1\n"
        "ori   $v0, $v0, 0x2C\n"
        "or    $v1, $v1, $v0\n"
        "sb    $v1, 48($sp)\n"
        "srl   $v1, $a1, 17\n"
        "andi  $v1, $v1, 0x180\n"
        "lbu   $v0, 16($s5)\n"
        "mflo  $t8\n"
        "sb    $v0, 49($sp)\n"
        "lbu   $v0, 17($s5)\n"
        "mult  $fp, $a3\n"
        "addu  $s1, $a2, $zero\n"
        "sb    $v0, 50($sp)\n"
        "srl   $v0, $a1, 23\n"
        "andi  $v0, $v0, 0x60\n"
        "or    $v1, $v1, $v0\n"
        "lui   $v0, 0x800\n"
        "sw    $t8, 112($sp)\n"
        "lbu   $a0, 18($s5)\n"
        "and   $v0, $a1, $v0\n"
        "sh    $v1, 96($sp)\n"
        "sb    $a0, 51($sp)\n"
        "mflo  $t8\n"
        "bnez  $v0, .L80050948\n"
        "sw    $t8, 120($sp)\n"
        "lui   $v1, 0x1000\n"
        "lw    $v0, 28($s5)\n"
        "ori   $v1, $v1, 0x1000\n"
        "bne   $v0, $v1, .L80050950\n"
        "addiu $v0, $zero, 1\n"
        "lw    $v0, 32($s5)\n"
        "nop\n"
        "bnez  $v0, .L80050950\n"
        "addiu $v0, $zero, 1\n"
        ".L80050948:\n"
        "j     gfx2D_BG0_OBJ_1B4\n"
        "sw    $zero, 72($sp)\n"
        ".L80050950:\n"
        "sw    $v0, 72($sp)\n"
        "lui   $a1, %hi(D_800AE620)\n"
        "addiu $a1, $a1, %lo(D_800AE620)\n"
        "lw    $v0, 0($a1)\n"
        "lw    $v1, 4($a1)\n"
        "lw    $a0, 8($a1)\n"
        "sw    $v0, 16($sp)\n"
        "sw    $v1, 20($sp)\n"
        "sw    $a0, 24($sp)\n"
        "lw    $v0, 12($a1)\n"
        "lw    $v1, 16($a1)\n"
        "lw    $a0, 20($a1)\n"
        "sw    $v0, 28($sp)\n"
        "sw    $v1, 32($sp)\n"
        "sw    $a0, 36($sp)\n"
        "lw    $v0, 24($a1)\n"
        "lw    $v1, 28($a1)\n"
        "sw    $v0, 40($sp)\n"
        "sw    $v1, 44($sp)\n"
        "addiu $s0, $sp, 16\n"
        "lw    $a1, 32($s5)\n"
        "jal   func_80053B20\n"
        "addu  $a0, $s0, $zero\n"
        "addu  $a0, $s0, $zero\n"
        "lh    $a1, 28($s5)\n"
        "lh    $a2, 30($s5)\n"
        "jal   gte_scale_matrix\n"
        "addiu $a3, $zero, 4096\n"
        ".set\treorder\n"
    ".end\tGsSortBg\n"
);

INCLUDE_ASM("asm/nonmatchings/800b_7", gfx2D_BG0_OBJ_1B4);

INCLUDE_ASM("asm/nonmatchings/800b_7", gfx2D_BG0_OBJ_4A0);

INCLUDE_ASM("asm/nonmatchings/800b_7", gfx2D_BG0_OBJ_4D8);

INCLUDE_ASM("asm/nonmatchings/800b_7", gfx2D_BG0_OBJ_658);

INCLUDE_ASM("asm/nonmatchings/800b_7", gfx2D_BG0_OBJ_698);

INCLUDE_ASM("asm/nonmatchings/800b_7", GsSortFastBg);

INCLUDE_ASM("asm/nonmatchings/800b_7", gfx2D_BG1_OBJ_648);

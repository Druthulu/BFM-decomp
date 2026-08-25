#include "common.h"

INCLUDE_ASM("asm/nonmatchings/800b", func_80047D3C);

INCLUDE_ASM("asm/nonmatchings/800b", InvSquareRoot);

__asm__(".text\n.align 2\n.globl func_80047E58\n.ent\tfunc_80047E58\n"
        "func_80047E58:\n.frame $sp,0,$31\n.mask 0x00000000,0\n.fmask 0x00000000,0\n"
        ".set\tnoreorder\n"
        "lw $t0, 0($a0)\n"
        "lw $t1, 4($a0)\n"
        "lw $t2, 8($a0)\n"
        "b .L80047EAC\n"
        "addu $a3, $ra, $zero\n"
        ".set\treorder\n.end\tfunc_80047E58\n");


/* VectorNormal @ 0x80047E6C -- HANDWRITTEN PsyQ libgte-style wrapper (cookbook §179-B/§179-C,
 * §265 form 1; byte-proven exemplars: func_80059234 in src/800c.c, func_800D0440 in
 * src/md_MAIN_003/md_MAIN_003.c).
 *
 * Tell-tales that this is NOT compiler output:
 *   - $ra is stashed in $a3 across the call and restored after
 *     (addu $a3,$ra,$zero / addu $ra,$a3,$zero) -- a hand-written leaf-caller idiom
 *     gcc-2.7.2 never emits;
 *   - the FINAL store (sw $t2,8($a1)) sits IN the jr $ra delay slot -- unreachable from a
 *     C function body, whose epilogue (jr $ra; nop) cc1 appends unconditionally;
 *   - callee func_80047EC8 is itself splat-marked "Handwritten function" (raw GTE sqr/gpf body).
 *
 * Hence the whole function is FILE-SCOPE basic asm (no enclosing C function => no generated
 * prologue/epilogue), transcribed 1:1 from asm/nonmatchings/800b/VectorNormal.s:
 *   - ".ent\t"/".end\t" with literal TABS: maspsx process_line special-cases ".ent\t" and
 *     emits a fresh ".set noreorder"; a plain ".set noreorder" line is swallowed as state only.
 *   - every displacement/immediate DECIMAL (maspsx int(operand) is base-10).
 *   - delay-slot contents (the jal's nop, the jr's sw) written by hand, matching the target,
 *     same as the banked func_80059234 / func_80059FC0 bodies.
 *   - no .frame/.mask/.fmask: frameless (nothing saved, sp untouched); the banked
 *     func_80059234 passed the whole-binary gate without them, proving the gate ignores
 *     non-text frame metadata.
 *
 * Symbol audit vs the target's own relocation lines: the ONLY relocation in the target is
 * the jal to func_80047EC8 (line 8 of the .s); spelled identically here. The function
 * references no data symbols, no jumptables, and no hi-lo pairs.
 *
 * INTEGRATION NOTE: this REPLACES the INCLUDE_ASM("asm/nonmatchings/800b", VectorNormal)
 * stub line in src/800b.c. The stub must be deleted, not kept beside this block -- a
 * leftover stub defines the same symbol twice and the whole-binary gate fails at link
 * scope (the §14b failure class match_one cannot see). Sibling VectorNormalSS (0x30,
 * lh/sh variant, same handwritten idiom) banks with the identical template; its
 * .L80047EAC label is dead text (single fall-through path).
 */
__asm__(
    ".text\n"
    ".align\t2\n"
    ".globl\tVectorNormal\n"
    ".ent\tVectorNormal\n"
    "VectorNormal:\n"
        ".set\tnoreorder\n"
        "lw    $t0, 0($a0)\n"
        "lw    $t1, 4($a0)\n"
        "lw    $t2, 8($a0)\n"
        "addu  $a3, $ra, $zero\n"
        "jal   func_80047EC8\n"
        "nop\n"
        "addu  $ra, $a3, $zero\n"
        "sw    $t0, 0($a1)\n"
        "sw    $t1, 4($a1)\n"
        "jr    $ra\n"
        "sw    $t2, 8($a1)\n"
        ".set\treorder\n"
    ".end\tVectorNormal\n"
);

INCLUDE_ASM("asm/nonmatchings/800b", VectorNormalSS);

INCLUDE_ASM("asm/nonmatchings/800b", func_80047EC8);

INCLUDE_ASM("asm/nonmatchings/800b", MatrixNormal);

INCLUDE_ASM("asm/nonmatchings/800b", gteMIMefunc);

INCLUDE_ASM("asm/nonmatchings/800b", SquareRoot12);

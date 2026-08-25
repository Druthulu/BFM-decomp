#include "common.h"

/*
 * func_80047D3C == PsyQ SquareRoot0(long a): hand-written GTE-assisted integer
 * square root (splat marks it "Handwritten function"). The argument goes
 * straight into the GTE (mtc2 $a0,$30 = lzcs), the leading-zero count comes
 * back (mfc2 $v0,$31 = lzcr), the mantissa is normalised, a table at
 * D_8006D8EC is indexed and the half-word result shifted out. Un-compilable
 * tells: direct cop2 transfers with hand-placed hazard nops, `sub`/`addi`
 * where cc1 emits `subu`/`addiu`, a dead `andi $t0,$v0,1`, a branch target
 * that doubles as the preceding `b`'s delay slot (0x80047D84), and a second
 * exit whose return value sits in the final `jr`'s delay slot. No -O2 C can
 * emit this, so per cookbook §265 the body is banked as a verbatim file-scope
 * __asm__ transcription of the target .s, with the full form-1 directive
 * scaffold (.ent/.frame/.end) used by the two gate-proven banked precedents.
 *
 * maspsx interaction: the leading ".set noreorder" is SPACE-formed so maspsx's
 * is_reorder tracker stays True and IT fills every empty branch delay slot --
 * so the nops after beq/bltz/b/jr are deliberately NOT written by hand. The
 * two mtc2 hazard nops ARE hand-written (maspsx knows nothing about cop2
 * latency), and so is the nop after `lh $t5,%lo(...)($t5)`: maspsx's
 * load-delay pass does not fire on this lh/base-reuse shape (measured).
 * Immediates are decimal (maspsx int()s them); %hi/%lo relocate correctly.
 *
 * Recovered C semantics:
 * long SquareRoot0(long a) {
 *     gte_ldLZCS(a); u = gte_stLZCR();
 *     if (u == 0x20) return 0;
 *     e = u & ~1;
 *     sh = (0x1f - e) >> 1;
 *     m = (e - 0x18 < 0) ? (a >> (0x18 - e)) : (a << (e - 0x18));
 *     return ((int)*(short *)&D_8006D8EC[(m - 0x40)] << sh) >> 12;
 * }
 */
__asm__(
    ".text\n"
    ".align 2\n"
    ".globl func_80047D3C\n"
    ".ent func_80047D3C\n"
    "func_80047D3C:\n"
    ".frame $sp, 0, $31\n"
    ".set noreorder\n"
    "mtc2 $4, $30\n"
    "nop\n"
    "nop\n"
    "mfc2 $2, $31\n"
    "addiu $1, $0, 32\n"
    "beq $2, $1, 3f\n"
    "andi $8, $2, 1\n"
    "addiu $10, $0, -2\n"
    "and $10, $2, $10\n"
    "addiu $9, $0, 31\n"
    "sub $9, $9, $10\n"
    "sra $9, $9, 1\n"
    "addi $11, $10, -24\n"
    "bltz $11, 1f\n"
    "sllv $12, $4, $11\n"
    "b 2f\n"
    "1:\n"
    "addiu $11, $0, 24\n"
    "sub $11, $11, $10\n"
    "srav $12, $4, $11\n"
    "2:\n"
    "addi $12, $12, -64\n"
    "sll $12, $12, 1\n"
    "lui $13, %hi(D_8006D8EC)\n"
    "addu $13, $13, $12\n"
    "lh $13, %lo(D_8006D8EC)($13)\n"
    "nop\n"
    "sllv $13, $13, $9\n"
    "srl $2, $13, 12\n"
    "jr $31\n"
    "nop\n"
    "3:\n"
    "jr $31\n"
    "addiu $2, $0, 0\n"
    ".set reorder\n"
    "nop\n"
    "nop\n"
    "nop\n"
    ".end func_80047D3C\n"
);

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

void gteMIMefunc()
{
    __asm__ __volatile__(
        ".set\tnoreorder\n"
        "sll    $6, $6, 3\n"
        "add    $6, $6, $5\n"
        "mtc2   $7, $8\n"
        ".L80048078:\n"
        "lw     $8, 0($5)\n"
        "lh     $10, 4($5)\n"
        "sra    $9, $8, 16\n"
        "andi   $8, $8, 65535\n"
        "mtc2   $8, $9\n"
        "mtc2   $9, $10\n"
        "mtc2   $10, $11\n"
        "nop\n"
        "nop\n"
        "cop2   0x198003D\n"
        "lw     $2, 0($4)\n"
        "lh     $7, 4($4)\n"
        "sra    $3, $2, 16\n"
        "andi   $2, $2, 65535\n"
        "addi   $5, $5, 8\n"
        "mfc2   $8, $9\n"
        "mfc2   $9, $10\n"
        "mfc2   $10, $11\n"
        "add    $2, $2, $8\n"
        "add    $3, $3, $9\n"
        "add    $7, $7, $10\n"
        "sh     $2, 0($4)\n"
        "sh     $3, 2($4)\n"
        "sh     $7, 4($4)\n"
        "addi   $4, $4, 8\n"
        "bne    $5, $6, .L80048078\n"
        "nop\n"
        ".set\treorder\n"
    );
}

__asm__(
    ".text\n"
    ".align 2\n"
    ".globl SquareRoot12\n"
    "SquareRoot12:\n"
    ".set\tnoreorder\n"
    "mtc2  $4, $30\n"
    "nop\n"
    "nop\n"
    "mfc2  $2, $31\n"
    "addiu $1, $0, 32\n"
    ".word 0x1041001d\n"
    "nop\n"
    "andi  $8, $2, 1\n"
    "addiu $10, $0, -2\n"
    "and   $10, $2, $10\n"
    "addiu $9, $0, 19\n"
    "sub   $9, $9, $10\n"
    "sra   $9, $9, 1\n"
    "addi  $11, $10, -24\n"
    ".word 0x05600003\n"
    "nop\n"
    "sllv  $12, $4, $11\n"
    ".word 0x10000003\n"
    "addiu $11, $0, 24\n"
    "sub   $11, $11, $10\n"
    "srav  $12, $4, $11\n"
    "addi  $12, $12, -64\n"
    "sll   $12, $12, 1\n"
    "lui   $13, %hi(D_8006D8EC)\n"
    "addu  $13, $13, $12\n"
    "lh    $13, %lo(D_8006D8EC)($13)\n"
    "nop\n"
    ".word 0x05200004\n"
    "nop\n"
    "sllv  $2, $13, $9\n"
    ".word 0x03e00008\n"
    "nop\n"
    "neg   $9, $9\n"
    ".word 0x03e00008\n"
    "srlv  $2, $13, $9\n"
    ".word 0x03e00008\n"
    "addiu $2, $0, 0\n"
    "nop\n"
    "nop\n"
    "nop\n"
    ".set\treorder\n"
);

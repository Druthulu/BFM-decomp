#include "common.h"


void LightColor(void)
{
    __asm__ __volatile__(
        ".set\tnoreorder\n"
        "lwc2   $9, 0($4)\n"
        "lwc2   $10, 4($4)\n"
        "lwc2   $11, 8($4)\n"
        "nop\n"
        "mvmva  1, 2, 3, 1, 1\n"
        "swc2   $9, 0($5)\n"
        "swc2   $10, 4($5)\n"
        "swc2   $11, 8($5)\n"
        ".set\treorder\n"
        : : : "memory");
}

INCLUDE_ASM("asm/nonmatchings/800b_2", DpqColorLight);


/* DpqColor3 @ 0x8004929C -- handwritten PsyQ depth-cue colour routine.
 * Splat marks this "Handwritten function": raw GTE assembly, not compiler
 * output --
 *   - three 32-bit colour loads straight into GTE regs $20/$21/$22 from the
 *     caller's argument pointers ($4/$5/$6), then the same pointer ($6)
 *     re-loaded into GTE reg $6,
 *   - `mtc2 $7,$8` writes the OT code from argument $7 into GTE reg $8,
 *   - one cop2-latency `nop` before `dpct` (depth-cue colour transform),
 *   - three result pointers read from the CALLER's frame at 0x10..0x24($sp)
 *     (incoming stack arguments, private calling convention) receiving
 *     swc2 stores of $20/$21/$22.
 * None of that is reachable from C, so the body is one full inline asm block
 * (cookbook §265 form 2; precedents func_800CBA44 / GsTMDfastG4GL).
 *
 * maspsx interaction:
 *   - leading `.set<TAB>noreorder` (literal tab) flips maspsx's is_reorder
 *     tracker; the trailing `.set<TAB>reorder` hands it back so maspsx fills
 *     the delay slot of gcc's own frameless-leaf epilogue `j $31` -- the
 *     target's trailing `jr $ra; nop` is therefore deliberately NOT
 *     transcribed.
 *   - every memory offset is DECIMAL (maspsx int() is base-10).
 *   - the hazard `nop` between mtc2 and dpct is transcribed literally;
 *     maspsx's load-delay pass fires on none of these instructions (no
 *     GTE-reg base reads), so nothing is auto-inserted.
 */
void DpqColor3(void)
{
    __asm__ __volatile__(
        ".set\tnoreorder\n"
        "lwc2   $20, 0($4)\n"
        "lwc2   $21, 0($5)\n"
        "lwc2   $22, 0($6)\n"
        "lwc2   $6, 0($6)\n"
        "mtc2   $7, $8\n"
        "nop\n"
        "dpct\n"
        "lw     $8, 16($29)\n"
        "lw     $9, 20($29)\n"
        "lw     $10, 24($29)\n"
        "swc2   $20, 0($8)\n"
        "swc2   $21, 0($9)\n"
        "swc2   $22, 0($10)\n"
        ".set\treorder\n"
        : : : "memory");
}

INCLUDE_ASM("asm/nonmatchings/800b_2", Intpl);

s32 *Square12(s32 *a0, s32 *a1)
{
    register s32 *out __asm__("$5");
    out = a1;
    __asm__ __volatile__(
        ".set\tnoreorder\n"
        "lwc2  $9, 0(%0)\n"
        "lwc2  $10, 4(%0)\n"
        "lwc2  $11, 8(%0)\n"
        "nop\n"
        "sqr   1\n"
        "swc2  $25, 0(%1)\n"
        "swc2  $26, 4(%1)\n"
        "swc2  $27, 8(%1)\n"
        ".set\treorder\n"
        : : "r"(a0), "r"(out) : "$9", "$10", "$11", "memory");
    return a1;
}

INCLUDE_ASM("asm/nonmatchings/800b_2", Square0);

void AverageZ3()
{
    __asm__ __volatile__(
        ".set\tnoreorder\n"
        "mtc2  $4, $17\n"
        "mtc2  $5, $18\n"
        "mtc2  $6, $19\n"
        "nop\n"
        "cop2  22544429\n"       /* avsz3 = 0x4B58002D */
        "mfc2  $2, $7\n"
        ".set\treorder\n"
    );
}

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

__asm__(".text\n.align 2\n.globl OuterProduct12\n.ent\tOuterProduct12\n"
"OuterProduct12:\n.frame $sp,0,$31\n.mask 0x00000000,0\n.fmask 0,0\n"
".set\tnoreorder\n"
"cfc2 $t5, $0\n"
"cfc2 $t6, $2\n"
"cfc2 $t7, $4\n"
"lw $t0, 0($a0)\n"
"lw $t1, 4($a0)\n"
"lw $t2, 8($a0)\n"
"ctc2 $t0, $0\n"
"ctc2 $t1, $2\n"
"ctc2 $t2, $4\n"
"lwc2 $11, 8($a1)\n"
"lwc2 $9, 0($a1)\n"
"lwc2 $10, 4($a1)\n"
"nop\n"
"op 1\n"
"swc2 $25, 0($a2)\n"
"swc2 $26, 4($a2)\n"
"swc2 $27, 8($a2)\n"
"ctc2 $t5, $0\n"
"ctc2 $t6, $2\n"
"ctc2 $t7, $4\n"
"jr $ra\n"
"nop\n"
".set\treorder\n.end\tOuterProduct12\n");

__asm__(".text\n.align 2\n.globl OuterProduct0\n.ent\tOuterProduct0\n"
"OuterProduct0:\n.frame $sp,0,$31\n.mask 0x00000000,0\n.fmask 0,0\n"
".set\tnoreorder\n"
"cfc2 $t5, $0\n"
"cfc2 $t6, $2\n"
"cfc2 $t7, $4\n"
"lw $t0, 0($a0)\n"
"lw $t1, 4($a0)\n"
"lw $t2, 8($a0)\n"
"ctc2 $t0, $0\n"
"ctc2 $t1, $2\n"
"ctc2 $t2, $4\n"
"lwc2 $11, 8($a1)\n"
"lwc2 $9, 0($a1)\n"
"lwc2 $10, 4($a1)\n"
"nop\n"
"op 0\n"
"swc2 $25, 0($a2)\n"
"swc2 $26, 4($a2)\n"
"swc2 $27, 8($a2)\n"
"ctc2 $t5, $0\n"
"ctc2 $t6, $2\n"
"ctc2 $t7, $4\n"
"jr $ra\n"
"nop\n"
".set\treorder\n.end\tOuterProduct0\n");

__asm__(".text\n.align 2\n.globl func_80049440\n.ent\tfunc_80049440\n"
        "func_80049440:\n.frame $sp,0,$31\n.mask 0x00000000,0\n.fmask 0,0\n"
        ".set\tnoreorder\n"
        "mtc2 $a0, $30\n"
        "nop\n"
        "nop\n"
        "mfc2 $v0, $31\n"
        "jr $ra\n"
        "nop\n"
        "nop\n"
        ".set\treorder\n.end\tfunc_80049440\n");

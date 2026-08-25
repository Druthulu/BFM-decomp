#include "common.h"


/* func_800495EC -- handwritten GTE SXY-load entry (splat: Handwritten function).
 * Three mtc2 stores of the incoming $a0-$a2 words into cop2 regs SXY0/SXY2/SXY1,
 * then TWO bare nops and NO jr: control falls through into func_80049600
 * (nclip + mfc2 $v0,$24 + jr $ra) in the next object. Any C function definition
 * would emit a jr $ra epilogue the target does not have, so the body is
 * transcribed verbatim as a file-scope asm block (cookbook §265 lane 1;
 * SetSZfifo3 form @ src/gsgap5.c:54). Decimal immediates only (maspsx).
 * Recovered semantics: gte_ldsxy3(a0,a1,a2); gte_nclip(); return gte_stMAC0();
 * via the fallthrough. */
__asm__(".text\n.align 2\n.globl func_800495EC\n.ent\tfunc_800495EC\n"
        "func_800495EC:\n"
        ".set\tnoreorder\n"
        "mtc2 $4, $12\n"
        "mtc2 $6, $14\n"
        "mtc2 $5, $13\n"
        "nop\n"
        "nop\n"
        ".set\treorder\n"
        ".end\tfunc_800495EC\n");

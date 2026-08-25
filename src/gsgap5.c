#include "common.h"

INCLUDE_ASM("asm/nonmatchings/gsgap5", SetVertex0);

INCLUDE_ASM("asm/nonmatchings/gsgap5", SetVertex1);

INCLUDE_ASM("asm/nonmatchings/gsgap5", SetVertex2);

void SetVertexTri(long *r0, long *r1, long *r2)
{
    __asm__ volatile(
        "lwc2 $0, 0( %0 );"
        "lwc2 $1, 4( %0 );"
        "lwc2 $2, 0( %1 );"
        "lwc2 $3, 4( %1 );"
        "lwc2 $4, 0( %2 );"
        "lwc2 $5, 4( %2 )"
        :
        : "r"(r0), "r"(r1), "r"(r2));
}

void SetRGBfifo(void* r0, void* r1, void* r2)
{
    __asm__ __volatile__ (
        "lwc2 $20, 0( %0 );"
        "lwc2 $21, 0( %1 );"
        "lwc2 $22, 0( %2 )"
        :
        : "r"( r0 ), "r"( r1 ), "r"( r2 )
        : "memory" );
}

INCLUDE_ASM("asm/nonmatchings/gsgap5", SetIR123);

INCLUDE_ASM("asm/nonmatchings/gsgap5", SetIR0);

/* SetSZfifo3 (0x80053A4C) -- handwritten GTE fifo-load wrapper (splat marks it
 * "Handwritten function"): three mtc2 stores of the incoming $a0-$a2 words into
 * cop2 data registers SZ1/SZ2/SZ3 ($17/$18/$19), then the frameless leaf return.
 * gcc-2.7.2 -O2 cannot emit bare cop2 register writes from C, so the body is
 * transcribed verbatim as a file-scope asm block (cookbook §265 lane 1,
 * func_800D0440 form @ src/md_MAIN_003/md_MAIN_003.c:329): the block carries the
 * .globl/.ent directives and the explicit jr $ra + nop tail -- no C codegen and
 * no declaration surface at all. No relocations, no symbol references.
 */
__asm__(".text\n.align 2\n.globl SetSZfifo3\n.ent\tSetSZfifo3\n"
        "SetSZfifo3:\n"
        ".set\tnoreorder\n"
        "mtc2 $4, $17\n"
        "mtc2 $5, $18\n"
        "mtc2 $6, $19\n"
        "jr $ra\n"
        "nop\n"
        ".set\treorder\n"
        ".end\tSetSZfifo3\n");

/* probe: naive spelling -- no volatile, no .set noreorder */
void SetSZfifo4()
{
    __asm__(
        "mtc2 $4, $16\n"
        "mtc2 $5, $17\n"
        "mtc2 $6, $18\n"
        "mtc2 $7, $19\n");
}

INCLUDE_ASM("asm/nonmatchings/gsgap5", SetSXSYfifo);

void SetRii()
{
    __asm__ __volatile__(
        ".set\tnoreorder\n"
        "ctc2 $4, $0\n"
        "ctc2 $5, $2\n"
        "ctc2 $6, $4\n"
        ".set\treorder\n");
}

INCLUDE_ASM("asm/nonmatchings/gsgap5", SetMAC123);

INCLUDE_ASM("asm/nonmatchings/gsgap5", SetData32);

INCLUDE_ASM("asm/nonmatchings/gsgap5", SetDQA);

INCLUDE_ASM("asm/nonmatchings/gsgap5", SetDQB);

INCLUDE_ASM("asm/nonmatchings/gsgap5", func_80053AD8);

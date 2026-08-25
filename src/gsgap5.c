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

INCLUDE_ASM("asm/nonmatchings/gsgap5", SetRGBfifo);

INCLUDE_ASM("asm/nonmatchings/gsgap5", SetIR123);

INCLUDE_ASM("asm/nonmatchings/gsgap5", SetIR0);

INCLUDE_ASM("asm/nonmatchings/gsgap5", SetSZfifo3);

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

INCLUDE_ASM("asm/nonmatchings/gsgap5", SetRii);

INCLUDE_ASM("asm/nonmatchings/gsgap5", SetMAC123);

INCLUDE_ASM("asm/nonmatchings/gsgap5", SetData32);

INCLUDE_ASM("asm/nonmatchings/gsgap5", SetDQA);

INCLUDE_ASM("asm/nonmatchings/gsgap5", SetDQB);

INCLUDE_ASM("asm/nonmatchings/gsgap5", func_80053AD8);

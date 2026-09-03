#include "common.h"
#include "../shared/engine_core.h"

/* ==== S74 overlay split (cookbook §426/§431) ================================
 * Split out of ov_SC03_105_jr_8017C8D0.c at vram 0x8018624C (file offset 0x5E0F4).
 * Reason: that ONE code subseg owned raw gcc switch jump tables in TWO
 * non-adjacent .rodata spans of the data tail —
 *   span 1  0x801B814C-0x801B822C  (func_801806F8, func_80180ABC, func_80180EC0,
 *                                   func_801813BC, func_801818E8, func_80181C84)
 *   span 2  0x801B8240-0x801B8290  (func_8018624C, func_801867D0)
 * A compiled object contributes exactly ONE contiguous .rodata run, so only one
 * span could ever carve and the other span's owners were unbankable at any effort
 * (jtbl_carve.py fails loud on it). This cut puts all six span-1 owners below the
 * boundary and both span-2 owners at/above it, so each piece carves its own span.
 * Contents are VERBATIM from the parent TU; only the INCLUDE_ASM subseg path changed. */

INCLUDE_ASM("asm/ov_SC03_105/nonmatchings/ov_SC03_105_jr_8018624C", func_8018624C);

#include "common.h"

extern s32 rand(void);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012A828(s32 a0, void *a1);
extern void func_801871C0(void *a0, s32 a1, s32 a2);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void (*D_8018E8E4[])(void);
extern void (*D_8018E9CC[])(void);

void func_80186680(s32 a0)
{
    s32 v0;

    if ((rand() & 0xFF) == 0) {
        func_801871C0((void *)a0, rand() % 5 + 1, 2);
    }

    if (func_8012BEE8(a0) != 0) {
        if ((rand() & 1) == 0) {
            func_8012A828(a0, D_8018E8E4);
            v0 = *(s32 *)(a0 + 0x6C);
            func_8012A828(v0, D_8018E9CC);
            *(s32 *)(a0 + 0x1C) = 0x72;
            func_801871C0((void *)a0, 7, 3);
            func_8002D4C8(0x728, 0);
        } else {
            *(s32 *)(a0 + 0x1C) = 0x5A;
        }
    }
}


extern void func_8012A828(s32 arg0, void *arg1);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern u8 D_801B2A58[];
extern u8 D_801B2C40[];

void func_8018676C(s32 a0) {
    s32 s0;

    s0 = a0;
    func_8012A828(a0, D_801B2A58);
    func_8012A828(*(s32 *)(s0 + 0x6C), D_801B2C40);
    func_8012C658(0x222, 0x8000, s0);
    *(s16 *)(s0 + 0x2) = 5;
    *(s16 *)(s0 + 0x34) = 0;
    *(s32 *)(s0 + 0x1C) = 0;
}


INCLUDE_ASM("asm/ov_SC03_105/nonmatchings/ov_SC03_105_jr_8018624C", func_801867D0);


extern s32 func_80178B18(s32, s32);

void func_80186AE8(void *arg0) {

    extern M2C_UNK D_8018EFBC;
    ((void (*)(void *, void *))func_80178B18)(arg0, &D_8018EFBC);
    *(s16 *)((s32)arg0 + 0x2) = 0x7;
    *(s16 *)((s32)arg0 + 0x34) = 0;
}

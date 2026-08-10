#include "common.h"

INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800CEED0);

INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800CEF04);

INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800CEFBC);

INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800CF010);

INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800CF078);

INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800CF104);

INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800CF300);

INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800CF370);

// Tier 1 (transcription) draft for func_800CF3A4 — md_MAIN_003
//
// NOTE ON TASK METADATA: the task handed to this agent claimed 437 instructions
// and pointed at .run/s46/snap_casc2/asm/md_MAIN_003/nonmatchings/md_MAIN_003/func_800CF3A4.s
// (a path that does not exist — that snapshot's md_MAIN_003 dir only contains
// func_800CF3E8.s and func_800D12D0.s). The live, in-tree, verified-immutable asm
// (asm/md_MAIN_003/nonmatchings/md_MAIN_003/func_800CF3A4.s) shows this function is
// genuinely tiny: "nonmatching func_800CF3A4, 0x44" — 0x44 bytes = 17 words including
// both delay-slot nops, i.e. 15 real instructions. This draft transcribes that real,
// on-disk function. See the STOPPING RULE report for the discrepancy.

extern s8 D_800D52BC[];
extern s32 D_800EC680;
extern u16 D_800B99E6;
extern u16 D_800B99E8;

extern void func_800183E0(s32 a0);

void func_800CF3A4(void) {
    func_800183E0((s32) &D_800D52BC);
    D_800B99E6 = 1;
    D_800B99E8 = (u16) D_800EC680;
}


INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800CF3E8);

INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800CFB3C);

INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800CFC1C);

INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800CFE00);

INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800CFEB4);

INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800CFFEC);

INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800D0100);

INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800D0174);

INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800D0204);

INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800D0268);

INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800D0440);

INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800D05B4);

INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800D0664);

INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800D06BC);

INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800D0740);

INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800D09A0);

INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800D0A7C);

INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800D0B1C);

INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800D0C50);

INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800D0D6C);

INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800D12D0);

INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800D1D14);

INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800D1E18);

INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800D1E58);

INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800D1E9C);

INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800D2394);

INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800D2454);

INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800D24D0);

INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800D2704);

INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800D27A0);

INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800D298C);

INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800D2A24);

INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800D2AA0);

INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800D2AD8);

INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800D2B64);

u16 func_800D2C00(s32 *a0) {
    return *(u16*)((s32)a0 + 0x0);
}


INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800D2C0C);

extern void func_800D2EF8(void);
void func_800D2C88(void) {
    func_800D2EF8();
}


INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800D2CA8);

INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800D2CE4);

INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800D2D20);

INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800D2D44);

INCLUDE_RODATA("asm/md_MAIN_003/nonmatchings/md_MAIN_003", D_800CEDF8);

INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800D2D68);

INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800D2E64);

INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800D2EF8);

INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800D2F88);

INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800D3020);

INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800D30B8);

INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800D30D0);

INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", D_800D3200);

INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800D3204);

INCLUDE_ASM("asm/md_MAIN_003/nonmatchings/md_MAIN_003", func_800D3234);

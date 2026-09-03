#include "common.h"

__asm__(
    ".text\n"
    ".align 2\n"
    ".globl func_80062388\n"
    ".ent\tfunc_80062388\n"
    "func_80062388:\n"
    ".frame $sp,0,$31\n"
    ".mask 0x00000000,0\n"
    ".fmask 0x00000000,0\n"
    ".set\tnoreorder\n"
    "lui $at, %hi(D_80072A24)\n"
    "jr $ra\n"
    "sw $a0, %lo(D_80072A24)($at)\n"
    ".set\treorder\n"
    ".end\tfunc_80062388\n"
);

extern s32 D_80072A24;

s32 func_80062394(void)
{
    return D_80072A24;
}

extern void func_80062768(void);
extern void func_8005CF08(void);
extern void func_800626F0(void);
extern void func_8005CF18(void);
extern s32 ChangeClearPAD(s32 mode);
extern void func_8006252C(void);
extern s32 PAD_init2(s32, s32, s32, s32);
extern s32 D_80072A24;

void func_800623A4(s32 a0, s32 a1, s32 a2, s32 a3)
{
    func_80062768();
    func_8005CF08();
    func_800626F0();
    func_8005CF18();
    ChangeClearPAD(0);
    func_8006252C();
    PAD_init2(a0, a1, a2, a3);
    D_80072A24 = 1;
}



extern void func_80062768(void);
extern void func_8005CF08(void);
extern void func_800626F0(void);
extern void func_8005CF18(void);
extern s32 ChangeClearPAD(s32 mode);
extern void func_8006252C(void);
extern void InitPAD2(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 D_80072A24;

void func_80062434(s32 a0, s32 a1, s32 a2, s32 a3)
{
    func_80062768();
    func_8005CF08();
    func_800626F0();
    func_8005CF18();
    ChangeClearPAD(0);
    func_8006252C();
    InitPAD2(a0, a1, a2, a3);
    D_80072A24 = 1;
}

extern void StartPAD2(void);
extern s32 ChangeClearPAD(s32 mode);
extern void func_800626C8(void);

s32 func_800624C4(void)
{
    StartPAD2();
    ChangeClearPAD(0);
    func_800626C8();
    return 1;
}

extern void func_800626DC(void);
extern void StopPAD2(void);
extern s32 func_800625A4(void);
extern s32 D_80072A24;

void func_800624F4(void)
{
    func_800626DC();
    StopPAD2();
    func_800625A4();
    D_80072A24 = 0;
}

INCLUDE_ASM("asm/nonmatchings/800c2_2", func_8006252C);

extern void func_8005CF08(void);
extern void func_8005CF18(void);
extern s32 SysDeqIntRP(s32 priority, void *intr);
extern unsigned char D_80078D08[];

s32 func_800625A4(void) {
    func_8005CF08();
    SysDeqIntRP(1, &D_80078D08);
    func_8005CF18();
    return 1;
}

extern u8 *D_80072A28;

s32 func_800625DC(void) {
    volatile s32 i;
    s32 frame_pad[2];

    (void)&frame_pad;
    *(u16 *)(D_80072A28 + 10) = 0;
    i = 10;
    if (--i != -1) {
        do {
        } while (--i != -1);
    }
    return 0;
}

s32 func_80062644(void) {
    extern s32 *D_80072A2C;
    s32 *p = D_80072A2C;

    if ((p[1] & 1) == 0) {
        return 0;
    }
    if ((p[0] & 1) != 0) {
        return 1;
    }
    if ((p[0] & 1) != 0) {
        return 1;
    }
    return 0;
}

__asm__(".word 0x00000000\n");

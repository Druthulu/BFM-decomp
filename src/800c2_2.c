#include "common.h"

__asm__(
    ".text\n"
    ".align 2\n"
    ".globl SetInitPadFlag\n"
    ".ent\tSetInitPadFlag\n"
    "SetInitPadFlag:\n"
    ".frame $sp,0,$31\n"
    ".mask 0x00000000,0\n"
    ".fmask 0x00000000,0\n"
    ".set\tnoreorder\n"
    "lui $at, %hi(D_80072A24)\n"
    "jr $ra\n"
    "sw $a0, %lo(D_80072A24)($at)\n"
    ".set\treorder\n"
    ".end\tSetInitPadFlag\n"
);

extern s32 D_80072A24;

s32 ReadInitPadFlag(void)
{
    return D_80072A24;
}

extern void _remove_ChgclrPAD(void);
extern void func_8005CF08(void);
extern void _patch_pad(void);
extern void func_8005CF18(void);
extern s32 ChangeClearPAD(s32 mode);
extern s32 func_8006252C(void);
extern s32 PAD_init2(s32, s32, s32, s32);
extern s32 D_80072A24;

void PAD_init(s32 a0, s32 a1, s32 a2, s32 a3)
{
    _remove_ChgclrPAD();
    func_8005CF08();
    _patch_pad();
    func_8005CF18();
    ChangeClearPAD(0);
    ((s32 (*)())func_8006252C)();
    PAD_init2(a0, a1, a2, a3);
    D_80072A24 = 1;
}



extern void _remove_ChgclrPAD(void);
extern void func_8005CF08(void);
extern void _patch_pad(void);
extern void func_8005CF18(void);
extern s32 ChangeClearPAD(s32 mode);
extern s32 func_8006252C(void);
extern void InitPAD2(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 D_80072A24;

void InitPAD(s32 a0, s32 a1, s32 a2, s32 a3)
{
    _remove_ChgclrPAD();
    func_8005CF08();
    _patch_pad();
    func_8005CF18();
    ChangeClearPAD(0);
    ((s32 (*)())func_8006252C)();
    InitPAD2(a0, a1, a2, a3);
    D_80072A24 = 1;
}

extern void StartPAD2(void);
extern s32 ChangeClearPAD(s32 mode);
extern void EnablePAD(void);

s32 StartPAD(void)
{
    StartPAD2();
    ChangeClearPAD(0);
    EnablePAD();
    return 1;
}

extern void DisablePAD(void);
extern void StopPAD2(void);
extern s32 func_800625A4(void);
extern s32 D_80072A24;

void StopPAD(void)
{
    DisablePAD();
    StopPAD2();
    func_800625A4();
    D_80072A24 = 0;
}

extern void func_8005CF08(void);
extern void func_8005CF18(void);
extern s32 SysDeqIntRP(s32 priority, void *intr);
extern s32 SysEnqIntRP(s32 priority, void *intr);
extern s32 func_800625DC(void);
extern s32 func_80062644(void);
extern s32 D_80078D0C;
extern u8 D_80078D08[];
extern s32 D_80078D14;

s32 func_8006252C(void) {
    s32 *p;
    s32 *q;
    s32 pri;

    func_8005CF08();
    pri = 1;
    __asm__ __volatile__("" : "=r"(pri) : "0"(pri));
    p = &D_80078D0C;
    __asm__ __volatile__("" : "=r"(p) : "0"(p));
    q = p - 1;
    p[0] = (s32)func_800625DC;
    p[1] = (s32)func_80062644;
    *(s32 *)D_80078D08 = 0;
    D_80078D14 = 0;
    SysDeqIntRP(pri, q);
    SysEnqIntRP(1, q);
    func_8005CF18();
    return 1;
}

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

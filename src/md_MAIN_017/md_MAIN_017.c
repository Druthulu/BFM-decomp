#include "common.h"

INCLUDE_ASM("asm/md_MAIN_017/nonmatchings/md_MAIN_017", func_800CAE0C);



void func_800CAE44(void *a0) {

    extern void (*D_800CB318[])(void);
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_800CB318[*(u8 *)((s32)a0 + 0x197)]();
}


extern void func_800CAEC0();
void func_800CAE88(void *a0) {
    func_800CAEC0(a0);
    *(u8 *)((s32)a0 + 0x197) += 1;
}


INCLUDE_ASM("asm/md_MAIN_017/nonmatchings/md_MAIN_017", func_800CAEC0);

void func_800CAF2C(u8 *a0) {
    extern s32 D_80078EC8;
    extern s32 D_80078EA4;
    extern void func_80165840(void);
    extern s32 func_80165A20(s32);

    if (D_80078EC8 == 0) {
        func_80165840();
        func_80165A20((s32)a0);
    } else {
        D_80078EA4 = 0;
    }
}


extern void func_80147364(s32 a, s32 b);
void func_800CAF7C(void) {
    func_80147364(0x4, 0x47C);
}


typedef struct { s32 w[8]; } Blk20;

void func_800CAFA0(void *a0) {
    extern u8 D_80078EC1;
    extern Blk20 D_800AE620;
    extern s32 func_80146A6C(s32, void *, s32, s32, s32, s32, s32);
    extern void func_80146C3C();
    extern void RotMatrixY(s32, void *);
    extern s32 func_80047948(s32);
    extern void func_8012F14C(s32, s32, s32);
    extern s32 func_80128ED8(s32, s32 *);

    struct { s16 x, y, z; } sv;
    Blk20 m;
    s32 *s2 = *(s32 **)((s32)a0 + 0x34);
    s32 *s3 = *(s32 **)((s32)a0 + 0x20);

    if (D_80078EC1 != 0x11) {
        func_80146A6C(3, a0, *(s16 *)((s32)a0 + 6), *(s16 *)((s32)a0 + 10), *(s16 *)((s32)a0 + 14), 0xAAAFFFA, 0xE000B400);
        func_80146C3C(a0);
    } else {
        m = D_800AE620;
        RotMatrixY((*(s32 *)((s32)a0 + 0x1C) << 5) + *(s32 *)((s32)a0 + 0x2C), &m);
        m.w[5] = *(s16 *)((s32)s2 + 6);
        m.w[6] = *(s16 *)((s32)s2 + 10);
        m.w[7] = *(s16 *)((s32)s2 + 14);
        sv.x = 0;
        sv.y = (func_80047948(((*(s32 *)((s32)a0 + 0x1C) & 0xF) << 8) + *(s32 *)((s32)a0 + 0x2C)) >> 9) - 0x14;
        sv.z = -0x40;
        func_8012F14C((s32)&m, (s32)&sv, (s32)&sv);
        if (*(s32 *)((s32)a0 + 0x1C) == 0) {
            func_80146A6C(3, a0, sv.x, sv.y, sv.z, 0xAAAFFFA, 0xE000B800);
        } else {
            *(s32 *)((s32)s3 + 4) &= 0x7FFFFFFF;
            *(u16 *)((s32)a0 + 6) = sv.x;
            *(u16 *)((s32)a0 + 10) = sv.y;
            *(u16 *)((s32)a0 + 14) = sv.z;
            func_80128ED8((s32)s3, (s32 *)((s32)a0 + 0x24));
        }
        (*(s32 *)((s32)a0 + 0x1C))++;
    }
}




void func_800CB190(void *a0) {

    extern void (*D_800CB350[])(void);
    D_800CB350[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_MAIN_017/nonmatchings/md_MAIN_017", func_800CB1CC);

INCLUDE_ASM("asm/md_MAIN_017/nonmatchings/md_MAIN_017", func_800CB2CC);

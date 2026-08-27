#include "common.h"

extern s32 func_800183E0(s32 *a0);
void func_800CAE0C(void) {

    extern s32 D_800CB538;
    func_800183E0(&D_800CB538);
}




void func_800CAE34(void *a0) {

    extern void (*D_800CB4FC[])(void);
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_800CB4FC[*(u8 *)((s32)a0 + 0x197)]();
}


extern void func_800CAEB0();
void func_800CAE78(void *a0) {
    func_800CAEB0(a0);
    *(u8 *)((s32)a0 + 0x197) += 1;
}


extern void func_801657A0();
extern s32 func_80165910();
extern void func_80147324(s32 arg0);
extern void func_8014B944(s32 a0, s32 a1, s32 a2);
extern void func_801655E4(s32 a0);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);

void func_800CAEB0(void *a0) {
    func_801657A0(a0);
    if (func_80165910((s32)a0) == 0) {
        func_80147324(0x7A3);
        func_8014B944((s32)a0, 0x100000, 1);
        func_801655E4((s32)a0);
    }
    func_80146A6C(0x21, a0, 0, 0, 0, 0, 0);
    *(u8 *)((s32)a0 + 0x197) += 1;
}


void func_800CAF38(void *a0) {

    extern s32 D_80078EC8;
    extern s32 D_80078EA4;
    extern void func_80165840(void);
    extern s32 func_80165A20(s32);

    if (D_80078EC8 == 0) {
        func_80165840();
        func_80165A20((s32)a0);
    } else {
        D_80078EA4 = 0xA00000;
    }
}


void func_800CAF8C(void) {
}

INCLUDE_ASM("asm/md_MAIN_021/nonmatchings/md_MAIN_021", func_800CAF94);

void func_800CB0C8(s32 arg0) {

    typedef struct { s32 w[8]; } Blk20;

    extern u8   D_80078EC1;
    extern u16  D_800B99DA;
    extern Blk20 D_800AE620;
    extern void func_80146C3C();
    extern s32  func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
    extern s32  func_80017DC4(void *a0, void *a1);
    extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
    extern void func_800D20C0(void *a0, void *a1, s32 a2);
    extern void func_800D23D0(void *a0);
    extern void RotMatrixYXZ(void *a0, void *a1);
    extern void RotMatrixZ(s32 a0, void *a1);
    extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
    extern void func_80048D9C(void *a0, void *a1);

    u16   vec[4];
    Blk20 blk;
    s16   sv[4];
    s16   rot[4];
    s16   mtx[16];
    s32 node;
    s32 ent;
    s32 e;
    s16 i;
    s16 t;

    node = *(s32 *)(arg0 + 0x20);
    if (D_80078EC1 == 2) {
        t = *(u16 *)(node + 0x1E) + 0x100;
        *(s16 *)(node + 0x1E) = t;
        if (t < 0x1000) {
            ent = *(s32 *)(arg0 + 0x34);
            sv[2] = 0x1000;
            sv[1] = 0x1000;
            sv[0] = 0x1000;
            func_80017DC4(sv, (void *)(arg0 + 0x38));
            sv[2] = 0;
            sv[0] = 0;
            sv[1] = -0x2C;
            func_8012F14C(*(s32 *)(ent + 0x20) + 0x34, (s32)sv, (s32)sv);
            { void *q0 = sv; void *q1 = rot;
              func_800D20C0(q0, q1, 5);
              __asm__ __volatile__("" : "=r"(q1)); }
            *(s16 *)(arg0 + 6)   = *(u16 *)&sv[0];
            *(s16 *)(arg0 + 0xA) = *(u16 *)&sv[1];
            *(s16 *)(arg0 + 0xE) = *(u16 *)&sv[2];
            { void *q2 = rot;
              func_800D23D0(q2);
              __asm__ __volatile__("" : "=r"(q2)); }
            { void *m1 = mtx;
              rot[2] = (D_800B99DA & 0x1F) << 7;
              RotMatrixYXZ(rot, m1);
              __asm__ __volatile__("" : "=r"(m1)); }
            func_80048D9C((void *)(arg0 + 0x38), mtx);
            return;
        }
        for (i = 0; i < 0x1000; i += 0x100) {
            e = func_80146A6C(0xE, (void *)arg0, 0, 0, 0, 1, 0);
            if (e != 0) {
                vec[0] = 0x48;
                vec[2] = 0;
                vec[1] = 0;
                blk = D_800AE620;
                RotMatrixZ(i, &blk);
                ApplyMatrixSV(&blk, vec, vec);
                func_8012F14C(arg0 + 0x38, (s32)vec, (s32)vec);
                *(s16 *)(e + 6)   = vec[0];
                *(s16 *)(e + 0xA) = vec[1];
                *(s16 *)(e + 0xE) = vec[2];
                *(Blk20 *)(e + 0x38) = *(Blk20 *)(arg0 + 0x38);
            }
        }
    }
    func_80146C3C(arg0);
}




void func_800CB33C(void *a0) {

    extern void (*D_800CB508[])(void);
    D_800CB508[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_MAIN_021/nonmatchings/md_MAIN_021", func_800CB378);

void func_800CB478(s32 param_1)
{
    extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
    extern void func_80146C3C();
    extern u8 D_80078EC1;
    s32 a1;
    s32 counter;

    a1 = *(s32 *)(param_1 + 0x34);
    if (D_80078EC1 == 2) {
        counter = *(s32 *)(param_1 + 0x1c) - 1;
        *(s32 *)(param_1 + 0x1c) = counter;
        if (counter == -1) {
            func_80146A6C(0x21, (void *)a1, 0, 0, 0, 0x8000, 0);
            *(s32 *)(param_1 + 0x1c) = 0x20;
        }
    } else {
        func_80146C3C(param_1);
    }
}


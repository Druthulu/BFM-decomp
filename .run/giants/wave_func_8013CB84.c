#include "common.h"

typedef struct { s32 a, b, c; } Rec12;
typedef struct { s32 a, b; s8 c; } __attribute__((packed, aligned(1))) Rec9;

extern s16 currentLocationId;
extern u8 D_80078EAF;
extern s32 D_801D9590;
extern s32 D_801D9588;
extern s32 D_801D958C;
extern s32 D_801D9580;
extern s32 D_801D9584;
extern s32 D_801D9594;
extern s32 D_801D95A0;
extern s32 D_801D95A8;
extern s32 D_801DAAA0;
extern s32 D_801DAA20;
extern s32 D_801DAA14[];
extern u8 D_801DA9C1;
extern u8 D_801DAB2E;
extern u8 D_801DAA9C;
extern Rec12 D_80187484[];
extern Rec9 D_8018744C[];
extern Rec9 D_801DAA78;

extern void func_8013DBE4();
extern void func_8013D9B0();
extern void func_8013D330(void);
extern void func_8013D178(void);
extern void func_8013CF68(void);

void func_8013CB84(void) {
    s32 loc = currentLocationId;
    s32 s0 = D_80078EAF;
    s32 ta, tb, tc, t;

    D_801DAAA0 = 0;
    if (D_801D9590 == 0 && s0 != D_801D9588) {
        ta = D_80187484[s0].a;
        tb = D_80187484[s0].b;
        tc = D_80187484[s0].c;
        D_801D9588 = s0;
        D_801DA9C1 = tc;
        D_801DAB2E = ta;
        D_801DAA9C = tb;
        D_801DAA78 = D_8018744C[s0];
        D_801D958C = 1;
        D_801D9580 = 1;
        if (D_801D95A0 & 2) {
            if (s0 == 4) { D_801DAA14[0] = 0x100; D_801DAA20 = 0x80; }
            if (s0 == 0) { D_801DAA14[0] = 0x100; D_801DAA20 = 0; }
        }
    }
    if (D_801D958C != 0) {
        t = D_801D9580 - 1;
        D_801D9580 = t;
        if (t == 0) {
            if (D_801D9590 == 0) {
                if ((D_801D95A0 & 2) && s0 == 4) {
                    if (D_801D95A8 != 0) func_8013DBE4(6);
                    else func_8013D9B0(6);
                } else {
                    if (D_801D95A8 != 0) func_8013DBE4(s0);
                    else func_8013D9B0(s0);
                }
                func_8013D330();
                func_8013D178();
                func_8013CF68();
                D_801D9580 = 2;
                if (D_801D958C != 0) {
                    if (D_801D95A0 & 2) {
                        if (s0 == 4) {
                            s32 *p = &D_801DAA20;
                            t = *p - 8;
                            *p = t;
                            if (t < 0) *p = 0;
                        } else if (s0 == 0) {
                            s32 *p = &D_801DAA20;
                            t = *p + 0x20;
                            *p = t;
                            if (t >= 0x81) *p = 0x80;
                        }
                    }
                } else if (D_801D95A0 & 2) {
                    if (s0 == 4) D_801DAA20 = 0;
                    if (s0 == 0) D_801DAA20 = 0x80;
                }
            } else {
                if (D_801D95A8 != 0) func_8013DBE4(5);
                else func_8013D9B0(5);
                D_801D9580 = 1;
            }
        }
    }
    D_801D9594 = 0;
    if (loc == 0x1010) {
        if (s0 == 3) {
            if (D_801D958C != 0) D_801D9594 = D_801D9584;
            else D_801D9594 = 0x1F;
        } else if (s0 == 4) {
            if (D_801D958C != 0) D_801D9594 = 0x1F - D_801D9584;
            else D_801D9594 = 0;
        }
    }
}

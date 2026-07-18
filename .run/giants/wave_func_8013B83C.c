#include "common.h"

typedef struct {
    s32 f0;    /* 0x00 */
    s16 f4;    /* 0x04 */
    s16 f6;    /* 0x06 */
    s16 f8;    /* 0x08 */
    s16 fa;    /* 0x0A */
    s32 fc;    /* 0x0C */
    s32 f10;   /* 0x10 */
    s32 f14;   /* 0x14 */
    s32 f18;   /* 0x18 */
} E_3B83C; /* 0x1C */

extern E_3B83C D_801DAA08[];
extern s32 D_801DAAA4;
extern s32 D_801DAAA8;
extern s32 D_801DAAAC;
extern s32 D_801DAAC0;
extern s32 D_801DAAD0;
extern s32 D_801DAB20;
extern s32 D_801DAB24;
extern s32 D_801DAB28;
extern s16 D_800B9A0E;

void func_80052D90(s32 a0, void *a1);
void func_8013BD74(void *a0, s32 a1);
void func_8013C08C(void *a0, s32 a1);

void func_8013B83C(s32 a0, s32 a1, s32 a2) {
    s32 i;

    D_801DAAC0 = 0;
    D_801DAAAC = 0;
    D_801DAAA8 = 0;
    D_801DAAA4 = 0;
    func_80052D90(0, &D_801DAAD0);
    if (a0 == 0) {
        return;
    }
    D_801DAB20 = a2 + 500;
    D_801DAB24 = a2;
    for (i = 0; i < 4; i++) {
        D_801DAA08[i].f0 = 0;
        D_801DAA08[i].f4 = D_801DAA08[i].f6 = D_801DAA08[i].f8 = 0x6000;
        D_801DAA08[i].fc = 0x100;
        D_801DAA08[i].f18 = 0;
    }
    switch (*(u8 *)a0) {
    case 0x42:
        if (D_800B9A0E == 0) {
            func_8013BD74(&D_801DAAC0, a0);
        } else {
            func_8013BD74(&D_801DAAC0, a1);
        }
        D_801DAB28 = 0;
        break;
    case 0x43:
        func_8013C08C(&D_801DAAC0, a0);
        D_801DAB28 = 1;
        break;
    case 0x44:
        func_8013C08C(&D_801DAAC0, a0);
        D_801DAB28 = 2;
        break;
    case 0x45:
        func_8013C08C(&D_801DAAC0, a0);
        D_801DAB28 = 3;
        break;
    case 0x46:
        func_8013C08C(&D_801DAAC0, a0);
        D_801DAB28 = 4;
        break;
    case 0x47:
        func_8013C08C(&D_801DAAC0, a0);
        D_801DAB28 = 5;
        break;
    case 0x48:
        func_8013C08C(&D_801DAAC0, a0);
        D_801DAB28 = 6;
        break;
    case 0x49:
        func_8013C08C(&D_801DAAC0, a0);
        D_801DAB28 = 9;
        break;
    case 0x4A:
        func_8013C08C(&D_801DAAC0, a0);
        D_801DAB28 = 0xC;
        break;
    case 0x4B:
        func_8013C08C(&D_801DAAC0, a0);
        D_801DAB28 = 0xD;
        break;
    case 0x4C:
        func_8013C08C(&D_801DAAC0, a0);
        D_801DAB28 = 0xE;
        break;
    case 0x4D:
        func_8013C08C(&D_801DAAC0, a0);
        D_801DAB28 = 0xF;
        break;
    case 0x4E:
        func_8013C08C(&D_801DAAC0, a0);
        D_801DAB28 = 0x10;
        break;
    }
}

/* BANK BLOCKER (Phase-29 crack-wave, 2026-07-18): match_one MATCH (272 ins, -O0) but DEFERRED —
 * (1) sweep ×138 is blocked by the Arm-A -O0-cluster splat wall (same as func_8013C414's family);
 * (2) ×1 needs -O0 jr-isolation (jr_isolate_all skips -O0 objects — the whale _o0b split precedent)
 *     + a D_801DAA08 decl reconcile. ×1-only value (~272 ins). Low ROI vs the sweepable cores. */

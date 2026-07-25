#include "common.h"

/* func_80183814 -- 5122 ins, 21-case jump-table state machine on *(u16*)(a0+0x34).
 * PARTIAL draft (NOT a match, and not close to one -- 15 of 21 case bodies are
 * empty stubs).  Decoded here: preamble, cases 0, 2, 5, 7, 10, 12, and the tail.
 *
 * MEASURED (match_one, 2026-07-25):
 *   DIFF  func_80183814   mine=666 ins, target=5122 ins, 5039 mismatched
 * That number is dominated by the 4456 instructions of case bodies not written.
 *
 * Region-aligned skeleton comparison (.run/beh/regions.py -- registers masked out,
 * relocations masked per tools/masked_diff; NOTE j/jal targets are fully masked so
 * cross-jumps are invisible to this metric):
 *   PROLOGUE+PREAMBLE  38 tgt ins    0 real diffs
 *   CASE0             363 tgt ins   76 real diffs, first at idx 278
 *   CASE2              22 tgt ins    0 real diffs
 *   CASE5              41 tgt ins    0 real diffs
 *   CASE7              20 tgt ins    0 real diffs
 *   CASE10             32 tgt ins    2 real diffs, first at idx 30
 *   CASE12            103 tgt ins   52 real diffs (scheduling + regalloc of the setup block)
 *   TAIL               19 tgt ins    9 real diffs (epilogue: 10 saved regs vs target's 8)
 *
 * Known blockers documented in the handoff:
 *  - the frame is 0xF8 = args(0x18) + sp18[0x20] + sp38[8] + sp40[0x14] + a DEAD
 *    128-byte local (`pad`) + 8 saved regs.  The 216-byte locals area is byte-exact.
 *  - gcc gives this draft 10 callee-saved regs (s0..s8+ra) vs the target's 8, because
 *    the truncated body has too little register pressure: from idx 278 of case 0 gcc
 *    CSEs the &D_8018E27C/&D_8018E288/... address constants into callee-saved regs,
 *    which the real (full) function cannot afford and rematerialises instead.
 *    => case 0 CANNOT be finished until the other cases raise the pressure.
 */

extern s32 func_8004787C(s32 a0);
extern void func_8017FDF8(s32 a0);
extern void func_8017F9AC(s32 a0, void *a1);
extern void func_8017D8A4(s32 a0, void *a1, void *a2, s32 a3, s32 a4);
extern void func_800599B8(void *a0, s32 a1);
extern s32 func_8012C658(s32 a0, s32 a1, s32 a2);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8017F5D4(s32 a0);
extern void func_801805D4(s32 a0, void *a1);
extern void func_8001C214(s32 a0, void *a1);
extern void func_8001D0E8(s32 a0, s32 a1, s32 a2);
extern void func_8012A828(s32 a0, void *a1);
extern void func_80016224(s32 a0, s32 a1);
extern void func_8012EC04(s32 param_1, s32 param_2, s32 *param_3);
extern void func_8012F14C(s32 *a0, s32 a1, s16 *a2);
extern s32 func_8012C51C(void *a0, s32 a1);
extern s32 rand(void);
extern s32 func_80178970(s32 a0);
extern void func_80178D18(s32 a0);

extern u8 D_8018E27C;
extern u8 D_8018E288;
extern u8 D_8018E294;
extern u8 D_8018E2A0;
extern u8 D_8018DFC0;
extern u8 D_8018DFC8;
extern u8 D_8018DFD0;
extern u8 D_8018DFD8;
extern u8 D_8018DFE0;
extern u8 D_8018DFE8;
extern s32 D_8018E034[];
extern s32 D_801BFCB4;
extern s32 D_801BFCBC;
extern u8 D_801BF540;
extern u8 D_801BFCCC;
extern u8 D_801BF5CC;
extern u8 D_801BF630;
extern u8 D_801BFCDC;
extern u8 D_801BF658;
extern u8 D_801BFCE4;
extern s32 D_801F61C0[];

void func_80183814(void *a0) {
    s32 sp18[8];
    s16 sp38[4];
    s16 sp40[10];
    s32 pad[32];
    s32 s3;
    s32 s0;
    s32 s1;
    s32 s4;
    s32 s5;
    s32 c;
    s32 r;
    s32 t;
    s32 idx;
    s32 ok;
    s32 *sp;

    s0 = func_8004787C(*(s16 *)((s32)a0 + 0xFC));
    s3 = s0 + (func_8004787C(*(s16 *)((s32)a0 + 0xFE)) >> 4);
    *(u16 *)((s32)a0 + 0xFE) = (*(u16 *)((s32)a0 + 0xFE) + 0x300) & 0xFFF;
    if (*(u16 *)((s32)a0 + 0x34) < 0x11) {
        *(s32 *)((s32)a0 + 0x8) =
            (*(s16 *)((s32)a0 + 0x8A) << 16) +
            (func_8004787C(*(s16 *)((s32)a0 + 0x104)) << 7);
        *(u16 *)((s32)a0 + 0x104) = *(u16 *)((s32)a0 + 0x104) + 0x40;
    }

    switch (*(u16 *)((s32)a0 + 0x34)) {
    case 0:
        *(s16 *)((s32)a0 + 0xFC) = *(s16 *)((s32)a0 + 0xFC) + 8;
        func_8017F9AC(s3, a0);
        func_8017D8A4(D_801BFCB4 + 0x3C, &D_8018E27C, &D_8018E27C + 0x30, s3, 1);
        func_8017D8A4(D_801BFCB4 + 0x48, &D_8018E288, &D_8018E288 + 0x30, s3, 1);
        func_8017D8A4(D_801BFCB4 + 0x54, &D_8018E294, &D_8018E294 + 0x30, s3, 1);
        func_8017D8A4(D_801BFCB4 + 0x60, &D_8018E2A0, &D_8018E2A0 + 0x30, s3, 1);
        func_8017FDF8(func_8004787C(*(s16 *)((s32)a0 + 0xFC)));

        r = func_8004787C(*(s16 *)((s32)a0 + 0xFC));
        c = (s16) * (u16 *)((s32)a0 + 0x102);
        if (r >= c) {
            t = (s16)(c / 455);
            if (t >= 10) {
                t = 9;
            }
            func_800599B8(&D_8018DFC0, D_8018E034[t]);
        }
        r = func_8004787C(*(s16 *)((s32)a0 + 0xFC));
        c = (s16) * (u16 *)((s32)a0 + 0x102);
        if (r >= c) {
            t = (s16)(c / 455);
            if (t >= 10) {
                t = 9;
            }
            idx = t + 9;
            func_800599B8(&D_8018DFC8, D_8018E034[idx]);
        }
        r = func_8004787C(*(s16 *)((s32)a0 + 0xFC));
        c = (s16) * (u16 *)((s32)a0 + 0x102);
        if (r >= c) {
            t = (s16)(c / 455);
            if (t >= 10) {
                t = 9;
            }
            idx = t + 0x12;
            func_800599B8(&D_8018DFD0, D_8018E034[idx]);
        }
        r = func_8004787C(*(s16 *)((s32)a0 + 0xFC));
        c = (s16) * (u16 *)((s32)a0 + 0x102);
        if (r >= c) {
            t = (s16)(c / 455);
            if (t >= 10) {
                t = 9;
            }
            idx = t + 0x1B;
            func_800599B8(&D_8018DFD8, D_8018E034[idx]);
        }
        r = func_8004787C(*(s16 *)((s32)a0 + 0xFC));
        c = (s16) * (u16 *)((s32)a0 + 0x102);
        if (r >= c) {
            t = (s16)(c / 455);
            if (t >= 10) {
                t = 9;
            }
            idx = t + 0x24;
            func_800599B8(&D_8018DFE0, D_8018E034[idx]);
        }
        r = func_8004787C(*(s16 *)((s32)a0 + 0xFC));
        c = (s16) * (u16 *)((s32)a0 + 0x102);
        if (r >= c) {
            t = (s16)(c / 455);
            if (t >= 10) {
                t = 9;
            }
            idx = t + 0x2D;
            func_800599B8(&D_8018DFE8, D_8018E034[idx]);
            ok = 1;
        } else {
            ok = 0;
        }
        if (ok != 0) {
            *(u16 *)((s32)a0 + 0x102) = *(u16 *)((s32)a0 + 0x102) + 0x1C7;
        }
        if (*(s16 *)((s32)a0 + 0xFC) != 0x200) {
            break;
        }
        s1 = 0;
        do {
            s0 = func_8012C658(0x3AC, 0, (s32)a0);
            if (s0 != 0) {
                *(u16 *)(s0 + 0xE) = *(u16 *)(s0 + 0xE) - 0x2D;
                *(u16 *)(s0 + 0xA) = *(u16 *)(s0 + 0xA) - 0x47;
                *(u16 *)(s0 + 0x6) = *(u16 *)(s0 + 0x6) - 5;
            }
            s1 += 1;
        } while (s1 < 0x10);
        func_8002D4C8(0xBBE, 0);
        func_8017F5D4(0x1000);
        func_8017D8A4(D_801BFCB4 + 0x3C, &D_8018E27C, &D_8018E27C + 0x30, 0x1000, 1);
        func_8017D8A4(D_801BFCB4 + 0x48, &D_8018E288, &D_8018E288 + 0x30, 0x1000, 1);
        func_8017D8A4(D_801BFCB4 + 0x54, &D_8018E294, &D_8018E294 + 0x30, 0x1000, 1);
        func_8017D8A4(D_801BFCB4 + 0x60, &D_8018E2A0, &D_8018E2A0 + 0x30, 0x1000, 1);
        *(u16 *)((s32)a0 + 0x34) = 1;
        func_801805D4(s3, a0);
        func_8001C214(*(s32 *)((s32)a0 + 0x20), &D_801BF540);
        func_8001D0E8(*(s32 *)((s32)a0 + 0x20), 0x280, 0x1E0);
        *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) = 0x400;
        func_8012A828((s32)a0, &D_801BFCBC);
        func_8017D8A4(D_801BFCBC + 0x3C, &D_8018E27C, &D_8018E27C + 0x30, s3, 1);
        func_8017D8A4(D_801BFCBC + 0x48, &D_8018E288, &D_8018E288 + 0x30, s3, 1);
        func_8017D8A4(D_801BFCBC + 0x54, &D_8018E294, &D_8018E294 + 0x30, s3, 1);
        break;
    case 1:
        break;
    case 2:
        if (*(s32 *)((s32)a0 + 0x1C) < 7) {
            func_80016224(0xFF, 0);
        }
        if ((*(s32 *)((s32)a0 + 0x1C) = *(s32 *)((s32)a0 + 0x1C) - 1) != 0) {
            break;
        }
        *(u16 *)((s32)a0 + 0x34) = 3;
        *(s16 *)((s32)a0 + 0xFC) = 0;
        *(u16 *)((s32)a0 + 0x102) = 0x1C7;
        func_8002D4C8(0xBB6, 0);
        break;
    case 3:
        break;
    case 4:
        break;
    case 5:
        if (*(s32 *)((s32)a0 + 0x1C) < 7) {
            func_80016224(0xFF, 0);
        }
        if ((*(s32 *)((s32)a0 + 0x1C) = *(s32 *)((s32)a0 + 0x1C) - 1) != 0) {
            break;
        }
        *(u16 *)((s32)a0 + 0x34) = 6;
        *(s16 *)((s32)a0 + 0xFC) = 0;
        func_8001C214(*(s32 *)((s32)a0 + 0x20), &D_801BF5CC);
        func_8001D0E8(*(s32 *)((s32)a0 + 0x20), 0x280, 0x1E0);
        *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) = 0x400;
        func_8012A828((s32)a0, &D_801BFCCC);
        func_8012C658(0x3AC, 1, (s32)a0);
        *(u16 *)((s32)a0 + 0x102) = 0x1C7;
        func_8002D4C8(0xBB9, 0);
        func_8002D4C8(0xC6F, 0);
        break;
    case 6:
        break;
    case 7:
        if (*(s32 *)((s32)a0 + 0x1C) < 7) {
            func_80016224(0xFF, 0);
        }
        if ((*(s32 *)((s32)a0 + 0x1C) = *(s32 *)((s32)a0 + 0x1C) - 1) != 0) {
            break;
        }
        *(u16 *)((s32)a0 + 0x34) = 8;
        *(s16 *)((s32)a0 + 0xFC) = 0;
        func_8002D4C8(0xBBC, 0);
        break;
    case 8:
        break;
    case 9:
        break;
    case 10:
        if (*(s32 *)((s32)a0 + 0x1C) < 7) {
            func_80016224(0xFF, 0);
        }
        if ((*(s32 *)((s32)a0 + 0x1C) = *(s32 *)((s32)a0 + 0x1C) - 1) != 0) {
            break;
        }
        *(u16 *)((s32)a0 + 0x34) = 0xB;
        *(s16 *)((s32)a0 + 0xFC) = 0;
        func_8001C214(*(s32 *)((s32)a0 + 0x20), &D_801BF630);
        func_8001D0E8(*(s32 *)((s32)a0 + 0x20), 0x280, 0x1E0);
        *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) = 0x400;
        func_8012A828((s32)a0, &D_801BFCDC);
        func_8002D4C8(0xBBF, 0);
        break;
    case 11:
        break;
    case 12:
        if (*(s32 *)((s32)a0 + 0x1C) < 7) {
            func_80016224(0xFF, 0);
        }
        s5 = 8;
        s4 = 0;
        sp = D_801F61C0;
        *(s32 *)((s32)a0 + 0x1C) = *(s32 *)((s32)a0 + 0x1C) - 1;
        func_8012EC04((s32)a0, 8, sp18);
        do {
            if (*sp % 80 == 0) {
                s32 p = *(s32 *)(*(s32 *)(*(s32 *)((s32)a0 + 0x20) + 0x24) + 0x20);
                if (*(s32 *)(p + 4) == 1) {
                    s1 = *(s32 *)(p + 0xC);
                } else {
                    s1 = p + (((*(u32 *)(p + 0xC) >> 2) << 2) + 0xC);
                }
                s0 = *(s32 *)(p + 0x10) - 1;
                s1 = s1 + (rand() % s0) * 8;
                func_8012F14C(sp18, s1, sp38);
                sp40[3] = 0x3C5;
                sp40[7] = s5;
                sp40[5] = 0;
                sp40[4] = 0;
                *(s32 *)&sp40[8] = s1;
                sp40[6] = 0x7FFF;
                sp40[0] = sp38[0];
                sp40[1] = sp38[1];
                sp40[2] = sp38[2];
                func_8012C51C(sp40, (s32)a0);
            }
            s4 += 1;
            sp += 1;
        } while (s4 < 8);
        if (*(s32 *)((s32)a0 + 0x1C) != 0) {
            break;
        }
        *(u16 *)((s32)a0 + 0x34) = 0xD;
        *(s16 *)((s32)a0 + 0xFC) = 0;
        func_8001C214(*(s32 *)((s32)a0 + 0x20), &D_801BF658);
        func_8001D0E8(*(s32 *)((s32)a0 + 0x20), 0x280, 0x1E0);
        func_8012A828((s32)a0, &D_801BFCE4);
        break;
    case 13:
        break;
    case 14:
        break;
    case 15:
        break;
    case 16:
        break;
    case 17:
        break;
    case 18:
        break;
    case 19:
        break;
    case 20:
        pad[0] = 0;
        break;
    }

    if (func_80178970((s32)a0) != 0) {
        func_80178D18((s32)a0);
        *(s16 *)((s32)a0 + 0x2) = 3;
    }
}

#include "common.h"

/* func_8003DC90 — main / src/sgap_4.c (191 ins).  Worked example: the SAME-TU neighbour
 * func_8003DF8C (§194-E) — same house style: `register s32 zr __asm__("$0")` + `i = arg0 + zr`
 * to spell the two argument copies, `(s16)argN` casts, and the `&= ~mask` tail blocks.
 *
 * Levers that closed it (in order):
 *   1. The reset/early "&= ~0x10" blocks must go through the SAME `q`/`k` locals as `p`
 *      (base pointer + byte offset).  Written the neighbour's way — recomputed from
 *      D_800C73D8[(s16)arg0] — cse cannot reach the multi-predecessor `reset:` block and the
 *      recompute costs 10 extra instructions AND forces arg0/arg1 into callee-saved regs
 *      (an extra `move`): 202 ins instead of 191.
 *   2. `if (w + 1 <= w + hv)` — NOT `if (w + hv >= w + 1)`.  Same `slt` operand order either
 *      way, but the source operand order decides which addend is EMITTED first (§3-T2).
 *   3. §49 (LUID dial), measured on `-dg`: sched2 does NOT reorder this triple — the emitted
 *      order IS the .greg order.  `&D_800C73D8[(s16)arg0]` expands index-first (sll,sra,la);
 *      a `base` local alone puts the `la` first (la,sll,sra).  The target wants sll,LA,sra, so
 *      the index cast is SPLIT across two statements (`t = arg0 << 16` … `t >> 16`) and the
 *      `base = D_800C73D8;` statement is threaded BETWEEN them.  Zero bytes: combine still
 *      folds `(t >> 16) * 4` back into the single `sra $v0,$v0,14`.
 */

extern s32 D_800C73D8[];
extern void func_80040DE8(s16, u16, u16, s16);
extern s32 func_80041354(s16, u16 *, u16 *);

void func_8003DC90(s32 arg0, s32 arg1)
{
    register s32 zr __asm__("$0");
    u16 w;
    u16 h;
    s32 p;
    s32 n;
    s32 i;
    s32 j;
    s32 *q;
    s32 k;
    s32 t;
    s32 *base;

    i = arg0 + zr;
    j = arg1 + zr;
    t = arg0 << 16;
    base = D_800C73D8;
    q = &base[t >> 16];
    k = (s16)arg1 * 0xB0;
    p = *q + k;
    n = *(s32 *)(p + 0xA0) - 1;
    *(s32 *)(p + 0xA0) = n;
    if (n < 0) {
        *(s32 *)(k + *q + 0x98) &= ~0x10;
        goto tail;
    }
    if (*(s16 *)(p + 0x4C) > 0) {
        if (n % *(s16 *)(p + 0x4C) != 0) {
            goto tail;
        }
        *(s16 *)(p + 0x4A) -= 1;
        if (*(s16 *)(p + 0x4A) < 0) {
            goto reset;
        }
        func_80041354(arg0 | (arg1 << 8), &w, &h);
        if (w + 1 <= w + *(s16 *)(p + 0x4A)) {
            func_80040DE8(arg0 | (arg1 << 8), w + 1, h + 1, 1);
        }
    } else if (*(s16 *)(p + 0x4C) < 0) {
        *(s16 *)(p + 0x4A) += *(s16 *)(p + 0x4C);
        if (*(s16 *)(p + 0x4A) < 0) {
            goto reset;
        }
        func_80041354(arg0 | (arg1 << 8), &w, &h);
        if (w - *(s16 *)(p + 0x4C) >= 0x7F && h - *(s16 *)(p + 0x4C) >= 0x7F) {
            func_80040DE8(arg0 | (arg1 << 8), 0x7F, 0x7F, 1);
        }
        if ((*(s32 *)(p + 0x9C) - *(s32 *)(p + 0xA0)) * -*(s16 *)(p + 0x4C) < *(s16 *)(p + 0x48)) {
            func_80040DE8(i | (j << 8), w - *(s16 *)(p + 0x4C), h - *(s16 *)(p + 0x4C), 1);
        }
    } else {
        goto tail;
    }
    goto check;
reset:
    func_80040DE8(arg0 | (arg1 << 8), 0x7F, 0x7F, 1);
    *(s32 *)(k + *q + 0x98) &= ~0x10;
check:
    if (*(s32 *)(p + 0xA0) == 0 || *(s16 *)(p + 0x4A) == 0) {
        *(s32 *)(D_800C73D8[(s16)i] + (s16)j * 0xB0 + 0x98) &= ~0x10;
    }
tail:
    func_80041354(i | (j << 8), (u16 *)(p + 0x5C), (u16 *)(p + 0x5E));
}



extern s32 D_800C73D8[];
extern void func_80040DE8(s16, u16, u16, s16);
extern s32 func_80041354(s16, u16 *, u16 *);

void func_8003DF8C(s32 arg0, s32 arg1)
{
    register s32 zr __asm__("$0");
    u16 w;
    u16 h;
    s32 p;
    s32 n;
    s32 i;
    s32 j;

    i = arg0 + zr;
    j = arg1 + zr;
    p = D_800C73D8[(s16)arg0] + (s16)arg1 * 0xB0;
    n = *(s32 *)(p + 0xA0) - 1;
    *(s32 *)(p + 0xA0) = n;
    if (n < 0) {
        *(s32 *)((s16)arg1 * 0xB0 + D_800C73D8[(s16)arg0] + 0x98) &= ~0x20;
        goto tail;
    }
    if (*(s16 *)(p + 0x4C) > 0) {
        if (n % *(s16 *)(p + 0x4C) != 0) {
            goto tail;
        }
        *(s16 *)(p + 0x4A) -= 1;
        if (*(s16 *)(p + 0x4A) > 0) {
            func_80041354(arg0 | (arg1 << 8), &w, &h);
            if (w - *(s16 *)(p + 0x4A) > 0 && h - *(s16 *)(p + 0x4A) > 0 && w != 1) {
                func_80040DE8(arg0 | (arg1 << 8), w - 1, h - 1, 1);
            } else {
                func_80040DE8(i | (j << 8), 1, 1, 1);
            }
        } else {
            *(s32 *)((s16)arg1 * 0xB0 + D_800C73D8[(s16)arg0] + 0x98) &= ~0x20;
        }
    } else {
        *(s16 *)(p + 0x4A) += *(s16 *)(p + 0x4C);
        if (*(s16 *)(p + 0x4A) > 0) {
            func_80041354(arg0 | (arg1 << 8), &w, &h);
            if (*(s16 *)(p + 0x48) >= (*(s32 *)(p + 0x9C) - *(s32 *)(p + 0xA0)) * -*(s16 *)(p + 0x4C)
                && -*(s16 *)(p + 0x4C) < w) {
                func_80040DE8(arg0 | (arg1 << 8), w + *(s16 *)(p + 0x4C), h + *(s16 *)(p + 0x4C), 1);
            } else {
                func_80040DE8(i | (j << 8), 1, 1, 1);
            }
        } else {
            *(s32 *)((s16)arg1 * 0xB0 + D_800C73D8[(s16)arg0] + 0x98) &= ~0x20;
        }
    }
    if (*(s32 *)(p + 0xA0) == 0 || *(s16 *)(p + 0x4A) == 0) {
        *(s32 *)(D_800C73D8[(s16)i] + (s16)j * 0xB0 + 0x98) &= ~0x20;
    }
tail:
    func_80041354(i | (j << 8), (u16 *)(p + 0x5C), (u16 *)(p + 0x5E));
}

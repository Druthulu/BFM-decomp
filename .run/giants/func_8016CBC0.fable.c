/* func_8016CBC0 — trail/afterimage RENDERER over the 0xC4-stride records at D_801D9CA0.
 * ×134 per-location family core (28,006 templatable ins). Sibling of func_80166994/func_8016CF04.
 *
 * ===== STATUS: PIN-FREE, match_one 46/209 (positional, CORRECT length 209). ROOT A CRACKED. =====
 *
 * This is the LOWEST-positional pin-free draft (the best next-tier seed by the gate metric).
 * Companion draft `func_8016CBC0.workhorse.c` (variant e4) cracks the harder root-B WORKHORSE
 * residual (scoped-merge) at the cost of an RC-6 secondary coupling — read `.fable.md` for the
 * full ladder and which base the next tier should take.
 *
 * PIN-FREE: YES. Zero `register __asm__("$N")` pins, zero hard-reg names. The only asm are
 *   generic-constraint zero-byte optimisation barriers (counter fences `__asm__("":"=r"(t):"0"(t))`
 *   + one input-only density anchor `__asm__("":: "r"(mat))`) — all ×134-safe (the §42e SIGABRTs
 *   are from FIXED-reg pins, which this has none of). Block-scoped decls, no file-scope footprint.
 *
 * WHAT LANDED vs the prior seed (m7, was 151/208):
 *   • ROOT A — mat/i $s4/$s5 swap: CRACKED with a PURE DENSITY DIAL (not coalescing!). mat(pseudo
 *     76) and i(77) both had live_length 163; mat had 7 refs, i had 9. `allocno_compare`
 *     (global.c:594) pri = floor_log2(n_refs)*n_refs/live_length: mat 2*7=14→858, i 3*9=27→1656 —
 *     i wins $s4 (the 7→8 ref jump crosses the floor_log2 boundary at 8, DOUBLING the multiplier).
 *     Fix: `__asm__("":: "r"(mat))` inside the outer-loop `if(active)` body (loop_depth 2 →
 *     reg_n_refs += 2, flow.c:2067) → mat 7→9 refs → ties i at 27 → mat wins $s4 by the creation-
 *     order tie-break (76<77, global.c:616). Byte-zero. This ALSO fixed the 208→209 length.
 *
 * RESIDUAL (root B, the ~46 masked): the vertex-block WORKHORSE. w0 loads to $a0 (mine) vs $v1
 *   (target); w3 to $a2/$a3 vs $a0. The target holds the whole w0→(short)w0→sum→av chain in ONE
 *   workhorse $v1 (a per-coord merged variable). Here w0 is a SEPARATE, MULTI-death (reused across
 *   3 coords) → GLOBAL allocno (local-alloc.c:472 gate REG_N_DEATHS==1 fails) → no destructive tie
 *   (K8: gcc-2.7.2 has NO global coalescing) → gets its own reg $a0. See `.fable.md`: this is
 *   CRACKABLE (workhorse.c does it via per-coordinate scoped-merge) but the crack trades into an
 *   RC-6 register-contention on $a1 (pv vs the coord-z accumulator) — the honest wall.
 *
 * Best pin-free draft (variant e1) follows.
 */
#include "common.h"

short func_8016CBC0(void) {
    typedef struct { u16 v[6]; } VtxR;
    typedef struct { u8 active, nv, cnt, col; VtxR verts[16]; } BlkR;
    typedef struct { s32 w[8]; } Blk20;
    extern BlkR  D_801D9CA0[];
    extern Blk20 D_800AE620;
    extern s32   func_80017758(void *a0, void *a1);

    u8 buf[0x90];
    u8  col;
    int uv;
    int cnt;
    u8 *vb;
    void *mat;
    int i;
    short ret;

    *(Blk20 *)(buf + 0x70) = D_800AE620;
    ret = 0;
    i = 0;
    mat = buf + 0x70;
    *(s32 *)(buf + 0x68) = 0x50000000;
    *(s32 *)(buf + 0x30) = 0x50000000;
    *(u8 *)(buf + 0x66) = 0;
    *(u8 *)(buf + 0x65) = 0;
    *(u8 *)(buf + 0x64) = 0;
    *(u8 *)(buf + 0x5E) = 0;
    *(u8 *)(buf + 0x5D) = 0;
    *(u8 *)(buf + 0x5C) = 0;
    *(u8 *)(buf + 0x2A) = 0;
    *(u8 *)(buf + 0x29) = 0;
    *(u8 *)(buf + 0x28) = 0;
    *(u8 *)(buf + 0x22) = 0;
    *(u8 *)(buf + 0x21) = 0;
    *(u8 *)(buf + 0x20) = 0;
    do {
        BlkR *e = &D_801D9CA0[(short)i];
        if (e->active != 0) {
            int tcnt;
            vb  = (u8 *)e + 4;
            uv  = e->nv;
            cnt = e->cnt;
            col = e->col;
            ret = ret + 1;
            __asm__("" :: "r"(mat));
            tcnt = cnt - 1;
            __asm__("" : "=r"(tcnt) : "0"(tcnt));
            cnt = tcnt;
            if (tcnt != -1) {
                do {
                    s32 uvm;
                    u8 *pv;
                    {
                        s32 po = (short)uv * 0xc;
                        s32 w0, w3, av;
                        u8 c8c;
                        pv = vb + po;
                        w0 = *(u16 *)(pv + 0x0);
                        *(short *)(buf + 0x00) = w0;
                        w3 = *(u16 *)(pv + 0x6);
                        *(short *)(buf + 0x40) = w3;
                        av = (u32)((short)w0 + (short)w3) >> 1;
                        *(short *)(buf + 0x38) = av;
                        *(short *)(buf + 0x08) = av;
                        w0 = *(u16 *)(pv + 0x2);
                        *(short *)(buf + 0x02) = w0;
                        w3 = *(u16 *)(pv + 0x8);
                        c8c = col >> 3;
                        uvm = uv - 1;
                        __asm__("" : "=r"(uvm) : "0"(uvm));
                        uv = uvm;
                        *(short *)(buf + 0x42) = w3;
                        av = (u32)((short)w0 + (short)w3) >> 1;
                        *(short *)(buf + 0x3A) = av;
                        *(short *)(buf + 0x0A) = av;
                        w0 = *(u16 *)(pv + 0x4);
                        *(short *)(buf + 0x04) = w0;
                        w3 = *(u16 *)(pv + 0xa);
                        *(u8 *)(buf + 0x59) = col;
                        *(u8 *)(buf + 0x25) = col;
                        *(u8 *)(buf + 0x5A) = c8c;
                        *(u8 *)(buf + 0x26) = c8c;
                        *(u8 *)(buf + 0x58) = c8c;
                        *(u8 *)(buf + 0x24) = c8c;
                        *(short *)(buf + 0x44) = w3;
                        av = (u32)((short)w0 + (short)w3) >> 1;
                        *(short *)(buf + 0x3C) = av;
                        *(short *)(buf + 0x0C) = av;
                    }
                    if ((int)(uvm << 16) < 0) uv = 0xf;
                    {
                        s32 po = (short)uv * 0xc;
                        s32 w0, w3, av;
                        u8 c84;
                        pv = vb + po;
                        col = col - 0xf;
                        c84 = col >> 3;
                        w0 = *(u16 *)(pv + 0x0);
                        *(short *)(buf + 0x10) = w0;
                        w3 = *(u16 *)(pv + 0x6);
                        *(short *)(buf + 0x50) = w3;
                        av = (u32)((short)w0 + (short)w3) >> 1;
                        *(short *)(buf + 0x48) = av;
                        *(short *)(buf + 0x18) = av;
                        w0 = *(u16 *)(pv + 0x2);
                        *(short *)(buf + 0x12) = w0;
                        w3 = *(u16 *)(pv + 0x8);
                        *(short *)(buf + 0x52) = w3;
                        av = (u32)((short)w0 + (short)w3) >> 1;
                        *(short *)(buf + 0x4A) = av;
                        *(short *)(buf + 0x1A) = av;
                        w0 = *(u16 *)(pv + 0x4);
                        *(short *)(buf + 0x14) = w0;
                        w3 = *(u16 *)(pv + 0xa);
                        *(u8 *)(buf + 0x61) = col;
                        *(u8 *)(buf + 0x2D) = col;
                        *(u8 *)(buf + 0x62) = c84;
                        *(u8 *)(buf + 0x2E) = c84;
                        *(u8 *)(buf + 0x60) = c84;
                        *(u8 *)(buf + 0x2C) = c84;
                        *(short *)(buf + 0x54) = w3;
                        av = (u32)((short)w0 + (short)w3) >> 1;
                        *(short *)(buf + 0x4C) = av;
                        *(short *)(buf + 0x1C) = av;
                    }
                    func_80017758(buf + 0x00, mat);
                    func_80017758(buf + 0x38, mat);
                    tcnt = cnt - 1;
                    __asm__("" : "=r"(tcnt) : "0"(tcnt));
                    cnt = tcnt;
                } while ((short)tcnt != -1);
            }
        }
        {
            int ti = i + 1;
            __asm__("" : "=r"(ti) : "0"(ti));
            i = ti;
            if ((short)ti >= 8) break;
        }
    } while (1);
    return ret;
}

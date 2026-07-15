/* func_8016CBC0 — trail/afterimage RENDERER over the 0xC4-stride records at D_801D9CA0
 * (sibling of func_80166994/func_8016CF04; same Blk struct: u8 f0..f3 header + 16x {6 verts}).
 * Loops entries 0..7; for each active entry, walks its `count` vertices building two GPU
 * primitive packets per step (pktA@buf+0x00, pktB@buf+0x38, shared mat@buf+0x70 <- D_800AE620)
 * and calls func_80017758(pkt, mat) twice. Returns (short) count of active entries.
 *
 * ===== STATUS: PIN-FREE NEAR-MISS 153/209 (masked) — ESCALATE TO FABLE5 (RC-6 qty-birth lock) =====
 *
 * PIN-FREE: YES. Zero `register __asm__("$N")` pins, zero hard-reg asm. The only asm are FOUR
 *   empty-string opaque-identity fences `__asm__("" : "=r"(t) : "0"(t))` (generic constraints,
 *   NO opcode) — pure optimisation barriers, milder than the flagship's in-out `lh`, fully
 *   ×134-safe (the §42e cc1-SIGABRTs come from FIXED-reg pins, which this has none of).
 *   Block-scoped typedefs/externs, no file-scope footprint, no //@EDIT (canon-sig already
 *   `extern short func_8016CBC0(void)`), so it splices + family_sweeps cleanly IF/when cracked.
 *
 * WHAT THE FLAGSHIP (func_80133CD4) LEVERS FIXED HERE (measured, match_one masked):
 *   • Lever B / opaque-copy fence (§36): the 3 counter chains (cnt initial + loopback, uv, i) now
 *     emit the target's compute-in-caller-temp-then-copy K8-no-coalesce form
 *     (`addiu vN,sN,-1; addu sN,vN,zero`) instead of the seed's in-place `addiu sN,sN,-1`.
 *     Root: `t = x-1; fence(t); x = t; test t` — the fence blocks cse/copy-prop from folding t
 *     into x, so x (a call-crossing GLOBAL allocno, global.c K8) keeps the copy. (The dB seed's
 *     PINS FORCED in-place counters — a pinned var is a hard reg, no coalescing decision at all.)
 *   • uv-split cured: the pin-free baseline scattered uv to a reload pseudo (201); the counter
 *     fence lands it back on a clean early pseudo -> $s1.
 *   • SINGLE reused inner-scope `pv` pointer (NOT block-local — the OPPOSITE of naive scoping):
 *     makes pv a GLOBAL allocno that global-alloc gives a1 AFTER local w3 grabs a0 — this fixed
 *     the whole first-vertex-block spine: (short)uv->v1, po->v0, pv-base->a1 (all == target).
 *
 * RESIDUAL (the ~56 masked mismatches — ONE interlinked RC-6 qty-birth/priority lock, §31/§27):
 *   1. w0-LOAD register: mine `lhu a0,0(a1)` vs target `lhu v1,0(a1)`. At the IDENTICAL register
 *      state (v0=po dead, v1=(short)uv dead, a1=pv live) gcc first-fits the w0 load to a0 (mine)
 *      vs v1 (target). Because the load lands in a0, its (short)/sum/av chain then lives in v1 —
 *      the target keeps the whole chain in v1 (workhorse). Merging w0/av (var reuse, Lever A)
 *      DOES pull w0->v1 but REGRESSES av in the 3rd unrolled vertex (v1->a0), net −13 (m8 144).
 *   2. w3 register: mine a2/a3 vs target a0 (target's 3rd w3 then merges into the dead pv-base
 *      a1: `lhu a1,0xa(a1)`). Pure local-alloc qty-birth order — w3 should be born early enough
 *      to win a0 and share it with uvm; mine's w3 qty is born late -> a2/a3.
 *   3. mat/i $s4/$s5 SWAP: mine mat=$s5,i=$s4; target mat=$s4,i=$s5. Both are call-crossing
 *      globals; both have 4 refs. gcc's allocno_compare (global.c:594) ranks i's priority
 *      (floor_log2(refs)*freq/live_length) strictly above mat's, so i takes $s4 first. Declaration
 *      order (col,uv,cnt,vb,mat,i,ret -> pseudos 72..78) WOULD give the target by the `v1-v2`
 *      tie-break IF priorities tied — they don't. NOT sensitive to: i-fence on/off (m6),
 *      break-vs-while outer loop (m10), pointer split (m5). Needs mat.pri >= i.pri, uncontrollable
 *      from C without a byte-visible mat ref (the block-copy is sp-relative; mat-relative mismatches).
 *   4. dbr: target steals `addiu v0,s5,1` (i+1) into the outer beqz delay slot (mine: `li v0,-1`),
 *      because the -1 test-constant is materialised AFTER the lbu loads in the target, freeing the
 *      slot. Downstream of the counter/pressure equilibrium.
 *   5. mine=208 vs target=209 (one load-delay nop the target leaves, mine's tighter schedule fills).
 *
 * LEVERS TRIED (match_one masked-match / 209): dB-seed pinned 155 · pin-free structural 140 ·
 *   +counter fences (m4) 140 · +single-pv spine (m7, THIS) 153 · +w0/av merge (m8) 144 ·
 *   no-uvm-fence (m7a) 146 · clean-while outer (m10) 153 · block-scoped pv (m5)=m4 · siblings
 *   func_80166994/CF04 are switch-shaped (no transferable vertex-loop idiom).
 *   => genuine gdb-on-cc1 ORACLE territory (§34): the w0-load/w3 qty-birth order + the mat/i
 *      allocno_compare priority are the two roots. Patch find_free_reg's qty pick (ffr2.gdb) +
 *      the allocno priority mid-compile to confirm each, then hunt the pin-free C form
 *      (flagship method). Confirms the prior agent's Fable5 verdict, now from a pin-free base.
 *
 * Best pin-free draft (m7, 153/209 masked in match_one) follows verbatim.
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

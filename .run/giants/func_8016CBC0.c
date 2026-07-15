/* func_8016CBC0 — trail/afterimage RENDERER over the 0xC4-stride records at D_801D9CA0
 * (sibling of func_80166994/func_8016CF04; same Blk struct: u8 f0..f3 header + 16x {6 verts}).
 * Loops entries 0..7; for each active entry, walks its `count` vertices building two GPU
 * primitive packets per step (pktA@buf+0x00, pktB@buf+0x38, shared mat@buf+0x70 <- D_800AE620)
 * and calls func_80017758(pkt, mat) twice. Returns (short) count of active entries.
 *
 * ============================ STATUS: NEAR-MISS 166/209 — ESCALATE TO FABLE5 ============================
 * Body/logic/constants/frame(0xC0) all byte-correct; residual = an interlinked gcc-2.7.2
 * REGALLOC/DBR knife-edge (RC-6 pressure-lock, §31/§27) — NOT the §43 class.
 *
 * §43 DOES NOT APPLY: §43 is the K&R s16-by-value-param idiom. func_8016CBC0 takes ZERO params
 *   (canon-sig `short func_8016CBC0(void)`), so there is no narrow-param wall to dissolve. The
 *   transferable part of §43 (block-scoped typedefs, no file-scope footprint) IS applied below;
 *   its "no pins" part does NOT hold here — with no params to anchor the allocation, the pin-free
 *   structural draft scatters ($s4/$s5 swap, uv->caller temp): 182 mismatch vs 166 with pins.
 *
 * //@EDIT: NONE required. The split stubs this as INCLUDE_ASM(...func_8016CBC0) (auto-spliced by
 *   rtu_match/harvest_verify). Canon-sig in engine_core.h DEFINE_func_8016D64C is already
 *   `extern short func_8016CBC0(void)` and its caller uses the return (`if (func_8016CBC0()==0)`),
 *   so NO return-type //@EDIT and NO ec_edit (contrast the sibling func_80166994 void->s32 flip).
 *
 * PINS: YES — 6 register __asm__ pins ($16/$17/$18/$20/$21/$22) forcing the col/uv/cnt/mat/i/ret
 *   $s-map. Load-bearing (removing them = 182). FLAG for ×134: register pins can cc1-SIGABRT in
 *   sibling TUs under family_sweep (§42e) — Fable5 should retire them when cracking the residual.
 *
 * RESIDUAL (the 43 aligned mismatches, all one interlinked RC-6/coalescing/dbr cluster):
 *   1. pv-base $a0(mine) vs $a1(target) in the FIRST vertex block, cascading the w3 half-loads to
 *      $a3 vs $a0. RTL-dump root cause: my loaded-value temps (w0/w3/av) are GLOBAL allocnos
 *      spanning the wraparound branch, so the pv-base local pseudo grabs $a0 (via an $a0/$a1
 *      copy-preference, greg: "84 preferences: 4 5 -> in 4"); the target's w3 temp is block-local
 *      and MERGES with the pv-base reg on the last load (`lhu $a1,0xa($a1)`), leaving base=$a1.
 *   2. dbr delay-slot steal: target steals `addiu $v0,$s5,1` (i+1) into the outer `beqz` slot;
 *      mine fills it with `li v0,-1`.
 *   3/4. counter "compute-in-caller-temp then move-to-$s" for i/cnt/uv (target
 *      `addiu $v0,$s2,-1; addu $s2,$v0,$zero`); mine coalesces to in-place `addiu $s2,$s2,-1`.
 *   5. ~6 load-delay `nop`s the target leaves (mine=203 vs target=209) — mine fills those slots.
 *
 * LEVERS TRIED (all regress or no-op — the RC-6 "every edit moves 20+ insns" tell):
 *   no-pins/structural 182 · giv-init fence on uvm (§34) 160 · block-local vertex temps 156 ·
 *   test-on-temp counter form 166(=) · opaque-copy cnt fence (kept, +1 -> 166).
 *   => genuine decomp-permuter / Fable5-reads-the-compiler-source territory (§30/§31/§27 cont.7d).
 *
 * Best draft (dB, 166/209 in real-TU rtu_match) follows verbatim.
 */
#include "common.h"

short func_8016CBC0(void) {
    typedef struct { u16 v[6]; } VtxR;
    typedef struct { u8 active, nv, cnt, col; VtxR verts[16]; } BlkR;
    extern BlkR  D_801D9CA0[];
    extern Blk20 D_800AE620;
    extern s32   func_80017758(void *a0, void *a1);

    u8 buf[0x90];   /* pktA@0x00, pktB@0x38, mat@0x70 */
    register u8  col __asm__("$16");
    register int uv  __asm__("$17");
    register int cnt __asm__("$18");
    u8 *vb;
    register void *mat __asm__("$20");
    register int i   __asm__("$21");
    register short ret __asm__("$22");

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
            vb  = (u8 *)e + 4;
            uv  = e->nv;
            cnt = e->cnt;
            col = e->col;
            ret = ret + 1;
            cnt = cnt - 1;
            __asm__("" : "=r"(cnt) : "0"(cnt));
            if (cnt != -1) {
                do {
                    s32 po, av, uvm;
                    s32 w0, w3;
                    u8 c8c, c84;

                    po = (short)uv * 0xc;
                    w0 = *(u16 *)(vb + po + 0x0);
                    *(short *)(buf + 0x00) = w0;
                    w3 = *(u16 *)(vb + po + 0x6);
                    *(short *)(buf + 0x40) = w3;
                    av = (u32)((short)w0 + (short)w3) >> 1;
                    *(short *)(buf + 0x38) = av;
                    *(short *)(buf + 0x08) = av;
                    w0 = *(u16 *)(vb + po + 0x2);
                    *(short *)(buf + 0x02) = w0;
                    w3 = *(u16 *)(vb + po + 0x8);
                    c8c = col >> 3;
                    uvm = uv - 1;
                    uv = uvm;
                    *(short *)(buf + 0x42) = w3;
                    av = (u32)((short)w0 + (short)w3) >> 1;
                    *(short *)(buf + 0x3A) = av;
                    *(short *)(buf + 0x0A) = av;
                    w0 = *(u16 *)(vb + po + 0x4);
                    *(short *)(buf + 0x04) = w0;
                    w3 = *(u16 *)(vb + po + 0xa);
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
                    if ((int)(uvm << 16) < 0) uv = 0xf;
                    po = (short)uv * 0xc;
                    col = col - 0xf;
                    c84 = col >> 3;
                    w0 = *(u16 *)(vb + po + 0x0);
                    *(short *)(buf + 0x10) = w0;
                    w3 = *(u16 *)(vb + po + 0x6);
                    *(short *)(buf + 0x50) = w3;
                    av = (u32)((short)w0 + (short)w3) >> 1;
                    *(short *)(buf + 0x48) = av;
                    *(short *)(buf + 0x18) = av;
                    w0 = *(u16 *)(vb + po + 0x2);
                    *(short *)(buf + 0x12) = w0;
                    w3 = *(u16 *)(vb + po + 0x8);
                    *(short *)(buf + 0x52) = w3;
                    av = (u32)((short)w0 + (short)w3) >> 1;
                    *(short *)(buf + 0x4A) = av;
                    *(short *)(buf + 0x1A) = av;
                    w0 = *(u16 *)(vb + po + 0x4);
                    *(short *)(buf + 0x14) = w0;
                    w3 = *(u16 *)(vb + po + 0xa);
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
                    func_80017758(buf + 0x00, mat);
                    func_80017758(buf + 0x38, mat);
                    cnt = cnt - 1;
                } while ((short)cnt != -1);
            }
        }
        i = i + 1;
    } while ((short)i < 8);
    return ret;
}

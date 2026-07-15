/* func_801670E4 (279 ins, ov_SC01_077_after) — STATUS: DIFF 23/279 (NOT a MATCH), PIN-FREE ×134-safe.
 *
 * Opus giant-cracker pass (2026-07-11), applying the func_80133CD4 flagship levers + the §31 codegen
 * map to the pin-free rewrite. Baseline was the PINNED seed at 48 (t=$2,zr=$0 biv + r1=$3 coloring,
 * ×1-only — SIGABRTs sibling TUs per §42e). This is PIN-FREE: NO `register __asm__("$N")` anywhere;
 * the only asm are one empty `__volatile__("")` fence + generic-constraint copies/anchors (=r/r/0,
 * real opcodes, no hard-reg names — the RC-12/S13 class, ×134-safe like the flagship's in-out lh).
 * Fewer diffs than the pinned seed (48→23) AND ×134-propagatable. Zero file-scope footprint
 * (all typedefs/externs block-scoped). No //@EDIT, no ec_edit (s32(s32×4) == canon-sig; void-return
 * as s32-no-return is byte-identical). `extern s32 func_80149350();` is for standalone match_one only
 * (ambient in the real TU; block-scoped no-proto = harmless redundant decl in-TU).
 *
 * ==== PIN-FREE LEVERS APPLIED (byte-verified stepwise, 74→23) ====
 *
 * L0. BIV, pin-free (replaces t=$2,zr=$0). The target's `addiu $v0,$s4,1 ; move $s4,$v0 ; sll;sra;
 *     slti;bnez` two-register K&R-s16 biv needs (a) a non-coalescing copy for `i=t` and (b) the temp
 *     in $v0. (a) generic-constraint asm copy `__asm__("addu %0,%1,$zero":"=r"(i):"r"(tN))` = the
 *     pin-free $0-add (RC-12): cse/combine can't fold it; assembles to `move $s4,$v0`. (b) a FRESH
 *     per-loop temp t1/t2/t3 (NOT one shared `t`) — a shared temp is a multi-block GLOBAL allocno
 *     stuck in $v1; each fresh temp is a local-alloc qty → lowest-free scratch = $v0 (§31 K8/K3).
 *     [fixed idx 102-104,167-169,263-265, the 3 biv loops.]
 *
 * L1. REGION-B CRACK — the §44-lever-5-NAMED wall "i=0/p-hoist co-location" (42 diffs → 0). sched1
 *     trace (`.i.sched` T-3) proved `i=0` (the L3 s4-reset) was WEDGED into the `lbu(c12)→addu(c12+0x60)`
 *     load-delay gap (S4 filler, sched.c:2632) because `col[1].g = *(param_1+0x12)+0x60` loaded AND
 *     used c12 adjacently — leaving i=0 as the only independent insn for the gap. FIX: load c12 EARLY,
 *     held across the color block, so the `li 0x20` (col[1].b/r) fills the gap and i=0 floats to the
 *     block top (idx 182), matching the target. p (D_80189A34) already floated correctly; the whole
 *     42-insn block-shift collapses. (Placement: p/i=0 kept just after the E68 call so m1/a1 stay
 *     above p per the target's `m1,a1,p,i=0` head order.)
 *
 * L2. THE d-SPLIT (15 diffs). `d` was ONE variable across BOTH center-adjust regions → a global
 *     allocno stuck in $a2 → the sum never got the local-alloc destructive tie (result reuses a dying
 *     operand reg). SPLIT into d1 (diff>>6 adjust) / d2 (>>1 + D_80126CE0*0x20) → each a local qty →
 *     `sra $v1,$v1,22` / `addu $v0,$v0,$v1` in-place (§31 K8/RC-4). Same class as L0's temp split and
 *     §44-Lever-3. [fixed idx 185-208.]
 *
 * L3. center.y-before-center.z source order (4 diffs). With d1 in $v1, writing center.y then center.z
 *     lets the scheduler read center.z EARLY into $a2 (the seed's "center.z-early forces d1→$v1"
 *     observation), matching the target's read-batch. [fixed idx 190-195.]
 *
 * L4. c12b LOCAL + INPUT-ONLY ANCHOR (2 diffs). block3's `col[1].g = c12+0x60` with the shared c12
 *     (block0+block3 global allocno) put +0x60 in a fresh $v0; a fresh single-set c12b would BOOST-sink
 *     (S2) back onto the addu and re-break Region-B. The §34 input-only anchor `__asm__("":: "r"(c12b))`
 *     right after the load makes the anchor c12b's first consumer → the boost sinks the def only to the
 *     anchor (stays EARLY, Region-B preserved) while c12b is a 1-death LOCAL qty → the +0x60 takes the
 *     destructive tie `addiu $v1,$v1,0x60` in-place. (The def+use re-tie `:"=r":"0"` REGRESSED +10 —
 *     input-only is the right dial.) [fixed idx 228-229.]
 *
 * ==== RESIDUAL 23 — two INTRINSIC §31 classes (Fable5 gdb-on-cc1 / permuter; NOT cheap-Opus-reachable) ====
 *
 *  (A) idx 19-24 (6): block0 — the func_80149350 arg-addresses `a1=&fr.center ; a2=a1` must interleave
 *      with the param stores BEFORE `p=D_80189A20 ; i=0`; mine emits p/i first. FENCE-LOCKED: the empty
 *      `__volatile__("")` (line ~107) is mandatory (without it p birthing-boosts to idx4, +250 diffs),
 *      but it walls the call arg-addrs (computed at the call, after the fence) behind p/i. The args have
 *      HIGH LUID (call site), p/i LOW LUID → p/i float above the args; no source order reaches it.
 *      pc-var-early + anchor CONFIRMED backfires (280 ins, +263 — matches the seed's v7). Fable5/permuter.
 *
 *  (B) idx 112-133 (17, DOMINANT): block2 pos-subtraction v0/v1 swap. `col[1].g=0xA0` holds $v0 (the L1
 *      bnez delay-slot steal) when sched1 places the D_801269A4 load — which is a pri-2 chain head
 *      (lw→subu→sw) that OUTRANKS the pri-1 col[1].g store (priority:1452; S3 — "C cannot LOWER a
 *      priority") → sched1 emits the load before the store (verified in `.i.sched`: D_801269A4 @1359 <
 *      col[1].g @2011) → D_801269A4→$v1, so pos[0]/pos[2]/pos[1] land $v1/$v0/$v1 (target: $v0/$v1/$v0).
 *      The seed cracked this with `r1 __asm__("$3")` (×1-only). Statement order (5 variants), the col/p
 *      swap, and fences are ALL byte-verified NO-OPs (RC-6/S11 coupling knife-edge). Fable5 (gdb-patch
 *      the $v0/$v1 grant) or permuter.
 *
 * Variant ladder (match_one, ov_SC01_077_after): pinned-seed 48 | pin-free asmcopy 74 → +biv-split 44
 *   → +Region-B(c12-early) 53→... (interacting) → +d-split 29 → +y/z 25 → +c12b-anchor 23 = THIS.
 *   pf2(p/i-top) 78, pf6b(cz-temp) 123, pf_c2(t-split) 30, pf_d1(retie) 35, pf_h1(pc-var) 280 = regressions.
 */
s32 func_801670E4(s32 param_1, s32 param_2, s32 param_3, s32 param_4) {
    typedef struct { s16 x, y, z, pad; } SVEC;
    typedef struct {
        SVEC center;                          /* 0x00 -> sp+0x10 */
        SVEC diff;                            /* 0x08 -> sp+0x18 */
        s32  pos[3];                          /* 0x10 -> sp+0x20 */
        s32  _pad1c;                          /* 0x1C -> sp+0x2C */
        SVEC v[4];                            /* 0x20 -> sp+0x30 */
        struct { u8 r, g, b, pad; } col[4];   /* 0x40 -> sp+0x50 */
        u32  code;                            /* 0x50 -> sp+0x60 */
        u32  _pad54;                          /* 0x54 -> sp+0x64 */
    } Fr;
    extern u8 D_80189A20[];
    extern u8 D_80189A0C[];
    extern u8 D_80189A34[];
    extern s32 D_801269A4;
    extern s32 D_801269A8;
    extern s32 D_801269AC;
    extern u16 D_80126CE0;
    extern void func_80017E68(void *a0, void *a1);
    extern void func_800D20C0(void *a0, void *a1, s32 a2);
    extern void func_800D23D0(void *a0);
    extern void RotMatrixYXZ(void *a0, void *a1);
    extern s32  func_80017758(void *a0, void *a1);
    extern s32  func_80017DC4(void *a0, void *a1);
    extern void func_80048EAC(void *a0, void *a1);
    extern s32  func_80149350();

    Fr fr;
    u8 m1[0x20];
    u8 m2[0x20];
    u8 *p;
    s32 i;
    s32 t;
    s32 t1;
    s32 t2;
    s32 t3;
    s32 r1;
    s32 arg0;
    s32 d1;
    s32 d2;
    s32 c12;
    u16 h;
    s32 c12b;

    arg0 = *(s32 *)(param_1 + 0x34);
    fr.v[1].z = 0;
    fr.v[1].y = 0;
    fr.v[1].x = 0;
    fr.v[3].z = 0;
    fr.v[2].z = 0;
    fr.v[0].z = 0;
    fr.col[1].b = 0x70;
    c12 = *(u8 *)(param_1 + 0x12);
    fr.center.x = param_2;
    fr.center.y = param_3;
    __asm__ __volatile__("");
    p = D_80189A20;
    i = 0;
    fr.col[0].b = 0;
    fr.col[0].g = 0;
    fr.col[0].r = 0;
    fr.col[2].b = 0;
    fr.col[2].g = 0;
    fr.col[2].r = 0;
    fr.col[3].b = 0;
    fr.col[3].g = 0;
    fr.col[3].r = 0;
    fr.code = 0x50000000;
    fr.center.z = param_4;
    fr.col[1].r = c12;
    fr.col[1].g = c12;
    ((void (*)(s32, void *, void *))func_80149350)(arg0, &fr.center, &fr.center);

    h = *(u16 *)&fr.center.x;
    *(s16 *)(param_1 + 6) = h;
    *(s32 *)(param_1 + 0x4C) = (s16)h;
    h = *(u16 *)&fr.center.y;
    *(s16 *)(param_1 + 0xA) = h;
    *(s32 *)(param_1 + 0x50) = (s16)h;
    h = *(u16 *)&fr.center.z;
    *(s16 *)(param_1 + 0xE) = h;
    *(s32 *)(param_1 + 0x54) = (s16)h;
    func_800D20C0(&fr.center, &fr.diff, 7);
    func_80017E68(&fr.center, m1);
    func_800D23D0(&fr.diff);
    RotMatrixYXZ(&fr.diff, m1);

L1:
    fr.v[0].x = (s8)*p++;
    fr.v[0].y = (s8)*p++;
    fr.v[2].x = (s8)*p++;
    fr.v[2].y = (s8)*p++;
    fr.v[3].x = (s8)*p++;
    fr.v[3].y = (s8)*p--;
    func_80017758(fr.v, m1);
    t1 = i + 1;
    __asm__("addu %0,%1,$zero":"=r"(i):"r"(t1));
    if ((s16)t1 < 4) goto L1;

    p = D_80189A0C;
    fr.col[1].g = 0xA0;
    fr.col[1].b = 0x10;
    fr.col[1].r = 0x10;
    t = D_801269A4 - fr.center.x;
    fr.pos[0] = t;
    i = 0;
    fr.v[3].y = 0;
    fr.v[2].y = 0;
    fr.v[0].y = 0;
    r1 = D_801269AC - fr.center.z;
    fr.pos[2] = r1;
    t = D_801269A8 - fr.center.y;
    fr.pos[1] = t;
L2:
    fr.v[0].x = (s8)*p++;
    fr.v[0].z = (s8)*p++;
    fr.v[2].x = (s8)*p++;
    fr.v[2].z = (s8)*p++;
    fr.v[3].x = (s8)*p++;
    fr.v[3].z = (s8)*p--;
    func_80017758(fr.v, (void *)(param_1 + 0x38));
    t2 = i + 1;
    __asm__("addu %0,%1,$zero":"=r"(i):"r"(t2));
    if ((s16)t2 < 4) goto L2;

    if (*(s32 *)(param_1 + 0x30) > 0) {
        d1 = (s16)*(u16 *)&fr.diff.x >> 6;
        fr.center.x = *(u16 *)&fr.center.x + d1;
        fr.center.y = *(u16 *)&fr.center.y + d1;
        fr.center.z = *(u16 *)&fr.center.z + d1;
        func_80017E68(&fr.center, m1);
        p = D_80189A34;
        i = 0;
        d2 = (*(u32 *)(param_1 + 0x30) >> 1) + D_80126CE0 * 0x20;
        fr.center.z = d2;
        fr.center.y = d2;
        fr.center.x = d2;
        func_80017DC4(&fr.center, m2);
        func_80048EAC(m2, m1);
        fr.v[3].z = 0;
        fr.v[2].z = 0;
        fr.v[0].z = 0;
        c12b = *(u8 *)(param_1 + 0x12);
        __asm__("" :: "r"(c12b));
        fr.col[1].b = 0x20;
        fr.col[1].r = 0x20;
        fr.col[3].b = 0;
        fr.col[3].r = 0;
        fr.col[2].b = 0;
        fr.col[2].r = 0;
        fr.col[0].b = 0;
        fr.col[0].r = 0;
        fr.col[3].g = 0;
        fr.col[2].g = 0;
        fr.col[0].g = 0;
        fr.col[1].g = c12b + 0x60;
L3:
        fr.v[0].x = (s8)*p++;
        fr.v[0].y = (s8)*p++;
        fr.v[2].x = (s8)*p++;
        fr.v[2].y = (s8)*p++;
        fr.v[3].x = (s8)*p++;
        fr.v[3].y = (s8)*p--;
        func_80017758(fr.v, m1);
        t3 = i + 1;
        __asm__("addu %0,%1,$zero":"=r"(i):"r"(t3));
        if ((s16)t3 < 8) goto L3;
    }
}

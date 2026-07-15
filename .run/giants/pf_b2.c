/* func_801670E4 (279 ins, ov_SC01_077_after) — STATUS: DIFF 48/279 (NOT a MATCH).
 * Best structural seed for Fable5 escalation. Independently reproduces the prior wave's
 * close=48 via the struct-typed sibling idiom (§43 / func_8016A290 / func_80167AE0, both
 * MATCHED in THIS TU), but with a CLEANER pin footprint (see below).
 *
 * NO //@EDIT, NO ec_edit needed:
 *   - s32(s32,s32,s32,s32) prototype == the split canon-sig `extern s32 func_801670E4(...)`.
 *   - void-return: declared s32 with no `return` (byte-identical to void; canon-sig is s32).
 *
 * §43 K&R s16-param: NOT APPLICABLE here (checked). param_2/3/4 are stored to the center
 * SVEC via `sh $aN` IMMEDIATELY and re-read from memory (`lh`/`lhu`) at every use — there is
 * NO in-place `sll aN,aN,16 ; sra aN,aN,16` triage tell. So plain s32 params are byte-identical
 * to K&R-promoted-int AND match the canon-sig with zero edits. (Contrast func_80166994, whose
 * params live in arg regs across calls → needed K&R.)
 *
 * STRUCTURE (all block-scoped, ×134-safe per §43): a `struct Fr` mirroring the sp+0x10 frame
 * (center/diff/pos/v[4]/col[4]/code), + m1/m2 matrix scratch. The 3 per-vertex loops use the
 * blessed biv idiom `t=$2 ; zr=$0 ; t=i+1 ; i=t+zr ; (s16)t<N` (shipped in func_80167AE0 &
 * func_8016A290 in this same TU — ×134-proven, no cc1-crash).
 *
 * PINS (flagged): t __asm__("$2"), zr __asm__("$0") = the biv 2-add copy (blessed, unavoidable).
 *   r1 __asm__("$3") = block2 pos-subtraction coloring crack (forces D_801269AC->$v1 so
 *   D_801269A4->$v0, reproducing the target's WAR-ordered store-0xA0-then-load pattern). This is
 *   the ONLY coloring pin; the prior seed also needed o=$19 and r0=$2 — BOTH eliminated here
 *   ($s3 for `o` falls out of the struct approach; $2 reused via t). r1 is byte-neutral (-14) and
 *   ×134-safe for this identical-across-overlays fn.
 *
 * RESIDUAL 48 = two IRREDUCIBLE instruction-scheduling tie-breaks (no reaching C-lever; the prior
 * wave AND this independent struct pass both floor at 48). §31 sched class; permuter/Fable5 only:
 *
 *  (A) block0 idx19-24 (6): the func_80149350 arg-addresses `a1=&center ; a2=a1` must interleave
 *      with the param stores (center.x@18, a1@19, center.y@20, a2@21) BEFORE `p=D_80189A20; i=0`
 *      (22-24). FENCE-LOCKED: the empty asm fence before p/i is mandatory (without it p HOISTS to
 *      idx4, +250mm); but it then walls the arg-addrs — computed at the call, after the fence —
 *      behind p/i. Regs already correct, so pins don't apply. No source order reaches it (v7 pc-
 *      var trick backfired to 280 ins).
 *
 *  (B) block3 idx182-... (42, DOMINANT): `i=0` (s4 reset) must land at idx182 — immediately after
 *      the HOISTED `p=D_80189A34` (s2@180, hoisted correctly from its pre-L3 source slot) and
 *      before the d-fanout (183). gcc hoists p to 180 but NEVER co-locates i=0 there: i=0 at the
 *      top of the if-block SINKS to idx227 (v4/v8); i=0 pre-L3 STAYS near L3 (v5); split i-top/
 *      p-late lands i=0 at 177, not 182 (v6, worse). This 1-slot i=0 misplacement cascades a
 *      whole-block shift. Riding on top: an interacting center.z load-timing diff — target reads
 *      center.z EARLY into $a2 (forcing d1 to stay in $v1); mine reads it late so d1 lands in $a2.
 *      Block3 d-pins make it WORSE (prior wave: 59) because the i-shift de-aligns them, so the
 *      i=0 POSITION must be fixed FIRST — a pure instruction move, permuter/Fable5 territory.
 *
 * Variants tried (rtu_match, ov_SC01_077_after): v1 88(base) -> v2 70(+fence) -> v3 69(pos-together)
 *   -> v4 52(+block2 r1 pin) -> v5 48(+block3 p/i-down, s1/s2 fixed) = THIS. v6 56, v7 242, v8 53,
 *   v9 63 all regressed. 48 is the floor.
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
    s32 d;
    s32 c12;
    u16 h;

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
    i = 0;
    fr.v[3].y = 0;
    fr.v[2].y = 0;
    fr.v[0].y = 0;
    fr.col[1].g = 0xA0;
    fr.col[1].b = 0x10;
    fr.col[1].r = 0x10;
    t = D_801269A4 - fr.center.x;
    fr.pos[0] = t;
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
        d = (s16)*(u16 *)&fr.diff.x >> 6;
        fr.center.x = *(u16 *)&fr.center.x + d;
        fr.center.z = *(u16 *)&fr.center.z + d;
        fr.center.y = *(u16 *)&fr.center.y + d;
        func_80017E68(&fr.center, m1);
        p = D_80189A34;
        i = 0;
        d = (*(u32 *)(param_1 + 0x30) >> 1) + D_80126CE0 * 0x20;
        fr.center.z = d;
        fr.center.y = d;
        fr.center.x = d;
        func_80017DC4(&fr.center, m2);
        func_80048EAC(m2, m1);
        fr.v[3].z = 0;
        fr.v[2].z = 0;
        fr.v[0].z = 0;
        c12 = *(u8 *)(param_1 + 0x12);
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
        fr.col[1].g = c12 + 0x60;
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

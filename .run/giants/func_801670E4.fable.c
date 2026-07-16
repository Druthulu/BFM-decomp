/* func_801670E4 (279 ins, ov_SC01_077_jr_8015AE2C) — Fable5 gdb-on-cc1 pass (2026-07-15).
 * STATUS: match_one DIFF 23/279 (NOT a MATCH), PIN-FREE, x134-safe. Body == the Opus seed
 * (.run/giants/func_801670E4.opus.c); I could not beat 23 pin-free. The value of this pass is
 * the RECLASSIFICATION + oracle PROOF of the dominant residual (see .fable.md).
 *
 * Residual 23 = region A (idx 19-24, 6: block0 fence-lock, a scheduling permutation) +
 *               region B (idx 112-133, 17, DOMINANT: the pos-subtraction v0/v1 swap).
 *
 * ==== KEY FABLE5 FINDING (corrects the seed's S3 verdict) ====
 * Region B is NOT an S3 scheduling-priority wall. The FINAL schedule already matches the target
 * byte-for-byte; the ENTIRE residual is register IDENTITY ($v0<->$v1 swapped on the t/r1 family).
 * PROVEN by gdb oracle: patching reg_renumber at reload entry (0x0815d4d7) to swap
 *   reg78(t)$v1->$v0, reg82(r1)$v0->$v1, reg132/136/140 (the D_ loads), reg127 (0x10 const)
 * makes cc1 emit region B BYTE-EXACT to the target, INCLUDING the col[1].g-store-before-A4-load
 * reordering (that reorder is a sched2 CONSEQUENCE of the register identity, not its cause).
 *
 * ROOT CAUSE: `t` (reused for pos[0]+pos[1], 2 deaths) is a GLOBAL allocno; `r1` (pos[2], 1 death)
 * is a LOCAL allocno. local-alloc runs before global-alloc, so the {AC,pos2} local qty grabs $v0
 * first-fit; this makes the global `t` conflict with $v0 -> forced to $v1. The target needs the
 * opposite coloring (t=$v0, r1=$v1). It is a self-consistent 2-coloring whose tie the allocator
 * resolves the wrong way; no pin-free C construct flips it (7 byte-verified failures, see .md).
 * The seed cracked it only with `r1 __asm__("$3")` (x1-only pin, unusable).
 *
 * NEXT TIER: decomp-permuter (may stumble on a globalizing perturbation), OR accept the x1 pin
 * for this ONE location if x134 propagation is later abandoned. Region A is likewise fence-locked.
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

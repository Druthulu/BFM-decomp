// @class: regalloc-order
// @stuck: 281/327 aligned-equal (325 vs 327 ins); frame 0x58 + $s0-$s5 assignment EXACT. Residual: (a) gcc emits `sltu $v0`+`addu $v1,$v0,$zero` for the `ne` boolean (coalescing) — mine writes $v1 direct; (b) blk-1 adjust: reorg STEALS the else-value into the branch delay (`bnez+addiu`) where target keeps `beqz;nop;j;addiu` (+4 ins); (c) blk-2 ne-block gets CROSS-JUMPED into the adjust tail (target's uses the entry-loaded $a1 for src->f3E so the tails differ; every attempt to hold it in a temp costs a reg and regresses -30).
//
// STRUCTURE (byte-derived, all verified against the .s):
//   $s3=st=&D_8011F7A8 (int base), $s1=st+0x48 (cach), $s2=st+0xE0 (flag), $s5=&D_80078E78 (src), $s4=param.
//   6 HUD fields synced src->cach with a chg-flag at [flag]: pairs 0x3A/0x3C and 0x3E/0x40, then 0x14(s32),
//   0x34(u16)+0x42(u8), 0x1A(s16), 0x4A(u8). Each: `if (cach==src) { if(!chg) goto skip; chg=0; } else {adjust}` + draw.
// KEY FINDINGS (reusable):
//   * Base MUST be `s32`, and the index expr written OFFSET-FIRST (`((p<<16)>>14) + st + 0x18`) — a `u8*` base
//     yields `addu rd,st,off`; the target is `addu rd,off,st`. Matches Ghidra's `(...>>0xe) + -0x7fee0840`.
//   * buf is 24 bytes, NOT Ghidra's 32: MIPS STARTING_FRAME_OFFSET = outgoing_args_size(20), so get_frame_size()
//     counts the 4-byte args-alignment gap. var=MIPS_STACK_ALIGN(4+24)=32 -> 32+24+28 -> 0x58. buf[32] gives 0x60.
//   * Block 1 uses RAW GLOBALS (D_8011F82C...) -> absolute lui/%lo; the ne-block uses `st+0x82`/`st+0x11C`
//     ($s3-relative) — both byte-confirmed; cse blocks end at labels so each region picks its own form.
//   * The zero-byte-ish `__asm__("" : "=r"(p2) : "0"(p2))` on param_1 is LOAD-BEARING: without it cse unifies
//     blk-5's two `st+off` uses across the if-merge label into a 7th callee reg -> frame 0x60 (whole-fn cascade).
//   * `ne` pinned to $v0 (+6 aligned). Pinning blk-5 e/sv REGRESSES (-16/-17).
extern u16 D_80078EB2, D_8011F82A, D_8011F82C, D_80078EB4, D_8011F8C4;
extern u8  D_8011F7A8;   /* st base  ($s3) */
extern u8  D_80078E78;   /* cur base ($s5) */
extern u8  D_8018A2B8[];
extern u8 *D_8018A23C[];

extern void  func_80176FF4(s32);
extern void  func_80177340(s32);
extern u32   func_801783D0(s32, s32);
extern void  func_80177F84(s32, s32);
extern void  func_80177DA8(s32, s32, s32);
extern void  func_80177AD4(s32, s32);
extern s32   func_80024054(u8 *, u8 *);
extern u32  *func_80178298(u32 *, u8 *, s32, s32);
extern s32   func_8005A600(s32, s32, s32, s32, s32);

void func_80176218(s32 param_1)
{
    s32 st   = (s32)&D_8011F7A8;   /* $s3 */
    s32 cach = st + 0x48;          /* $s1 */
    s32 flag = st + 0xE0;          /* $s2 */
    s32 cur  = (s32)&D_80078E78;   /* $s5 */
    u8 buf[24];
    register s32 ne __asm__("$2");
    u16 sA;

    /* ---- block 1: raw-global pair 0x3A/0x3C ---- */
    sA = D_80078EB2;
    ne = (sA != D_8011F82A);
    if (D_8011F82C == D_80078EB4) {
        if (ne == 0 && D_8011F8C4 == 0) goto L340;
    } else {
        s32 d = (s16)(D_8011F82C - D_80078EB4);
        if (d < 0) {
            if (d < -10) D_8011F82C = D_8011F82C + 2;
            else         D_8011F82C = D_8011F82C + 1;
        } else {
            if (d > 10)  D_8011F82C = D_8011F82C - 2;
            else         D_8011F82C = D_8011F82C - 1;
        }
        *(u16 *)(flag + 0x3C) = 1;
        *(u16 *)(cach + 0x3A) = *(u16 *)(cur + 0x3A);
        goto L328;
    }
    if (ne) {
        *(u16 *)(st + 0x82)  = sA;
        *(u16 *)(st + 0x11C) = 1;
    } else {
        *(u16 *)(st + 0x11C) = 0;
    }
L328:
    func_80176FF4(*(s32 *)(((param_1 << 16) >> 14) + st + 0x18));
L340:

    /* ---- block 2: pair 0x3E/0x40 ---- */
    ne = (*(u16 *)(cur + 0x3E) != *(u16 *)(cach + 0x3E));
    if (*(u16 *)(cach + 0x40) == *(u16 *)(cur + 0x40)) {
        if (ne == 0 && *(u16 *)(flag + 0x40) == 0) goto L444;
    } else {
        s32 d = (s16)(*(u16 *)(cach + 0x40) - *(u16 *)(cur + 0x40));
        u16 nc;
        if (d < 0) {
            nc = *(u16 *)(cach + 0x40) + 2;
            if (-11 < d) nc = *(u16 *)(cach + 0x40) + 1;
        } else {
            nc = *(u16 *)(cach + 0x40) - 1;
            if (10 < d) nc = *(u16 *)(cach + 0x40) - 2;
        }
        *(u16 *)(cach + 0x40) = nc;
        *(u16 *)(flag + 0x40) = 1;
        *(u16 *)(cach + 0x3E) = *(u16 *)(cur + 0x3E);
        goto L3E8;
    }
    if (ne) {
        *(u16 *)(cach + 0x3E) = *(u16 *)(cur + 0x3E);
        *(u16 *)(flag + 0x40) = 1;
    } else {
        *(u16 *)(flag + 0x40) = 0;
    }
L3E8:
    {
        s32 s0b = ((param_1 << 16) >> 14) + st;
        u16 cc;
        s32 pp;
        func_80177340(*(s32 *)(s0b + 0x18) + 0x104);
        cc = *(u16 *)(cach + 0x40);
        pp = *(s32 *)(s0b + 0x28);
        if (cc < 100)
            *(u8 *)(pp + 0x5D) = D_8018A2B8[cc / 5];
        else
            *(u8 *)(pp + 0x5D) = 0;
    }
L444:

    /* ---- block 3: field 0x14 (s32) ---- */
    if (*(s32 *)(cach + 0x14) == *(s32 *)(cur + 0x14)) {
        if (*(s32 *)(flag + 0x14) == 0) goto L4D0;
        *(s32 *)(flag + 0x14) = 0;
        goto L4A8;
    } else {
        s32 d = *(s32 *)(cur + 0x14) - *(s32 *)(cach + 0x14);
        s32 nd;
        if (d > 0) {
            nd = *(s32 *)(cach + 0x14) + 1;
            if (9 < d) nd = *(s32 *)(cach + 0x14) + 10;
        } else {
            nd = *(s32 *)(cach + 0x14) - 10;
            if (-10 < d) nd = *(s32 *)(cach + 0x14) - 1;
        }
        *(s32 *)(cach + 0x14) = nd;
        *(s32 *)(flag + 0x14) = 1;
    }
L4A8:
    {
        u32 r = func_801783D0(*(s32 *)(cach + 0x14), 0);
        func_80177F84(*(s32 *)(((param_1 << 16) >> 14) + st + 0x18) + 0x208, r);
    }
L4D0:

    /* ---- block 4: field 0x34 (u16) + 0x42 (u8) ---- */
    if (*(u16 *)(cur + 0x34) != *(u16 *)(cach + 0x34)) {
        *(u16 *)(cach + 0x34) = *(u16 *)(cur + 0x34);
        *(u16 *)(flag + 0x34) = 1;
        *(u8 *)(cach + 0x42) = *(u8 *)(cur + 0x42);
    } else {
        if (*(u16 *)(flag + 0x34) == 0) goto L558;
        *(u16 *)(flag + 0x34) = 0;
    }
    {
        u16 e = 999;
        s16 r;
        if (*(u16 *)(cach + 0x34) < 1000) e = *(u16 *)(cach + 0x34);
        r = (s16)func_801783D0((s16)e, 4);
        func_80177DA8(*(s32 *)(((param_1 << 16) >> 14) + st + 0x18) + 0x294,
                      (s32)r, *(u8 *)(cach + 0x42));
    }
L558:

    /* ---- block 5: field 0x1A (s16) ---- */
    if (*(s16 *)(cach + 0x1A) != *(s16 *)(cur + 0x1A)) {
        *(s16 *)(cach + 0x1A) = *(s16 *)(cur + 0x1A);
        *(s16 *)(flag + 0x1A) = 1;
    } else {
        if (*(s16 *)(flag + 0x1A) == 0) goto L63C;
        *(s16 *)(flag + 0x1A) = 0;
    }
    {
        u16 f = *(u16 *)(cach + 0x1A);
        s32 e = *(s32 *)(((param_1 << 16) >> 14) + st + 0x18);
        s16 sv = 0x200;
        s32 i6, i4;
        if ((f & 1) == 0) sv = *(u16 *)(st + 0x16) + 0x65;
        *(s16 *)(e + 0x32A) = sv;
        {
            s32 t = (((s16)f / 15) & 3) * 15;
            i6 = func_801783D0(((s16)f / 15) * 0x10000 >> 0x12, 8);
            i4 = func_801783D0((t * 0x10000) >> 16, 0);
        }
        {
            s32 p2 = param_1;
            __asm__("" : "=r"(p2) : "0"(p2));
            func_80177AD4(*(s32 *)(((p2 << 16) >> 14) + st + 0x18) + 800,
                          (i6 + i4) * 0x10000 >> 0x10);
        }
    }
L63C:

    /* ---- block 6: field 0x4A (u8) ---- */
    if (*(u8 *)(cur + 0x4A) != *(u8 *)(cach + 0x4A)) {
        *(u8 *)(cach + 0x4A) = *(u8 *)(cur + 0x4A) & 0x7F;
        *(u8 *)(flag + 0x4A) = 1;
    } else {
        if (*(u8 *)(flag + 0x4A) == 0) return;
        *(u8 *)(flag + 0x4A) = 0;
    }
    {
        s32 s0b = ((param_1 << 16) >> 14) + st;
        u8 *arg = D_8018A23C[*(u8 *)(cach + 0x4A)];
        u32 *p = (u32 *)(*(s32 *)(s0b + 0x18) + 900);
        func_80024054(arg, buf);
        p = func_80178298(p, buf,
                          (s16)(*(u16 *)(st + 0x14) + 0x39),
                          (s16)(*(u16 *)(st + 0x16) + 0x5B));
        func_8005A600((s32)p, 0, 0, 0x15, 0);
        *p = ((u32)((u8 *)p - 0x14) & 0xffffff) | 0x2000000;
        *(u32 **)(s0b + 0x20) = p;
    }
}

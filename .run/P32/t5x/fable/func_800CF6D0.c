/* func_800CF6D0 — md_MAIN_007 (-O2). Builds six 0x18-byte "SPRT with its own tpage" primitives
 * (tag / 0xE10000xx draw-mode word / rgb+code 0x64 / xy / uv+clut / wh) at the D_800A5E60 prim
 * cursor and addPrim()s each onto OT word [0] of the frame's ordering table
 * (D_800AA60C + D_800B9A02 * 0x4000), then republishes the advanced cursor.  Four 256-wide tiles
 * at (arg0-0xA0 + 0x100*i, arg1-0x78) plus a fixed 2 x (0xA0 x 0x100) backdrop.
 * Twin: md_MAIN_009/func_800CD92C (banked, §501-H) — same shape, same prologue weave.
 *
 * MATCH 249/249, match_one AND rtu_match (real TU), ZERO register pins (P32 T5x, Fable).
 * The prior 137-plateau's residual ("sched1 rank_for_schedule class tie") was misattributed —
 * read from the -dS/-dR/-df dumps and the 2.7.2 source it is three separate mechanisms:
 *
 *  1. sched2 (NOT sched1) split the field stores around the `lhu D_800B9A02`: sched.c:838-845
 *     true_dependence exempts a /s (struct-member) store at a VARYING address in NON-QImode from
 *     conflicting with a non-/s FIXED-address read, so `p->clut/x0/y0/w/h/tpage` were ready one
 *     clock before the lhu, won schedule_select's potential-hazard rule (store > load > ALU) and
 *     then blocked the loads for a cycle ("blocking insn ... for 1 cycles").  QImode /s stores get
 *     no exemption, hence the QI-before/HI-after grouping.  CAST stores (`*(u16 *)(p + 0x12)`)
 *     are not /s, conflict with the lhu, and all 13 stay before it in source (LUID) order.
 *  2. The OT write MUST be a /s access (the P_TAG bitfield, §351): only the same exemption lets
 *     `D_800A5E60 = p` (non-/s, fixed) float above block 6's OT write (target idx 243-244).
 *  3. `la D_800AA60C` -> $t2 and 0xFF000000 -> $t3 is a local-alloc qty_compare tie decided by
 *     FLOW's ref count: `ob` must be assigned BEFORE block 1 and used in block 1's tag-side read
 *     too (13 refs, like the twin's compiler-made `la` pseudo).  combine then folds the symbol
 *     back into that first use (3-insn merge, the la def is re-emitted as newi2pat), giving the
 *     target's raw-symbol `lui $at/addu/lw %lo` for read 1 and `addu ..,$t2` for the other 11 —
 *     but flow counted 13 refs before combine ran (combine.c never adjusts reg_n_refs), so la
 *     (13 refs, life 171) outranks mhi (13 refs, life 183).  `ob` assigned AFTER the first read
 *     (the T3 draft) is 12 refs and loses by 1.2% -> the 24-row $t2/$t3 swap.
 *     Side effect: the folded first-read sum temp (r90) survives the merge with reg_n_refs = 2
 *     (combine.c:2313/2336 only zero it for a deleted i2; here the la def is newi2pat), is in no
 *     insn, so reload1.c alter_reg gives it a 4-byte slot -> the 8-byte-rounded `vars= 8` that IS
 *     the target's 0x18 frame.  So the T3 draft's `u32 pad[2]` must go (with it: frame 0x20).
 *  Everything else is the twin's byte-proven shape: the multi-set tag RMW `t = *p; t &= FF00;
 *  t |= v; *p = t` (no birthing boost -> the tag load fills the lhu->sll gap and the tpage
 *  constants float to the top, §501-H), `v` computed BEFORE `t &= 0xFF000000`, the double mask
 *  `(ot & m24) & m24` (m24 = 19 refs -> $t1), `x0 = arg0 + 0x100` as an expression (the last one
 *  ties into $a0), chained `*(p+8) = *(p+9) = *(p+0xA) = 0x80` (stores 0xA, 9, 8).
 *  TU spelling: the TU declares `extern void func_800CF6D0(s32 a0, u32 a1);` — define it so.
 */
extern u8 *D_800A5E60;
extern u8 D_800AA60C[];
extern s16 D_800B9A02;

void func_800CF6D0(s32 arg0, u32 arg1) {
    u8 *p;
    typedef struct { u32 addr:24; u32 len:8; } P_TAG;
    u8 *ob;
    u32 m24;

    p = D_800A5E60;
    arg0 -= 0xA0;
    arg1 -= 0x78;
    ob = D_800AA60C;

    *(u8 *)(p + 0x3) = 5;
    *(u32 *)(p + 0x4) = 0xE1000089;
    *(u8 *)(p + 0xB) = 0x64;
    *(u16 *)(p + 0x12) = 0x7940;
    *(u8 *)(p + 0x8) = *(u8 *)(p + 0x9) = *(u8 *)(p + 0xA) = 0x80;
    *(s16 *)(p + 0xC) = arg0;
    *(s16 *)(p + 0xE) = arg1;
    *(u8 *)(p + 0x10) = 0;
    *(u8 *)(p + 0x11) = 0;
    *(s16 *)(p + 0x14) = 0x100;
    *(s16 *)(p + 0x16) = 0x100;
    m24 = 0xFFFFFF;
    {
        u32 v = (*(u32 *)((s32)ob + (((u16)D_800B9A02) << 14)) & m24) & m24;
        u32 t = *(u32 *)p;
        t &= 0xFF000000;
        t |= v;
        *(u32 *)p = t;
    }
    ((P_TAG *)(u32 *)((s32)ob + (((u16)D_800B9A02) << 14)))->addr = (u32)p;
    p += 0x18;

    *(u8 *)(p + 0x3) = 5;
    *(u32 *)(p + 0x4) = 0xE100008B;
    *(u8 *)(p + 0xB) = 0x64;
    *(u16 *)(p + 0x12) = 0x7940;
    *(u8 *)(p + 0x8) = *(u8 *)(p + 0x9) = *(u8 *)(p + 0xA) = 0x80;
    *(s16 *)(p + 0xC) = arg0 + 0x100;
    *(s16 *)(p + 0xE) = arg1;
    *(u8 *)(p + 0x10) = 0;
    *(u8 *)(p + 0x11) = 0;
    *(s16 *)(p + 0x14) = 0x100;
    *(s16 *)(p + 0x16) = 0x100;
    {
        u32 v = (*(u32 *)((s32)ob + (((u16)D_800B9A02) << 14)) & m24) & m24;
        u32 t = *(u32 *)p;
        t &= 0xFF000000;
        t |= v;
        *(u32 *)p = t;
    }
    ((P_TAG *)(u32 *)((s32)ob + (((u16)D_800B9A02) << 14)))->addr = (u32)p;
    p += 0x18;

    *(u8 *)(p + 0x3) = 5;
    *(u32 *)(p + 0x4) = 0xE100008D;
    *(u8 *)(p + 0xB) = 0x64;
    *(u16 *)(p + 0x12) = 0x7940;
    *(u8 *)(p + 0x8) = *(u8 *)(p + 0x9) = *(u8 *)(p + 0xA) = 0x80;
    *(s16 *)(p + 0xC) = arg0 + 0x200;
    *(s16 *)(p + 0xE) = arg1;
    *(u8 *)(p + 0x10) = 0;
    *(u8 *)(p + 0x11) = 0;
    *(s16 *)(p + 0x14) = 0x100;
    *(s16 *)(p + 0x16) = 0x100;
    {
        u32 v = (*(u32 *)((s32)ob + (((u16)D_800B9A02) << 14)) & m24) & m24;
        u32 t = *(u32 *)p;
        t &= 0xFF000000;
        t |= v;
        *(u32 *)p = t;
    }
    ((P_TAG *)(u32 *)((s32)ob + (((u16)D_800B9A02) << 14)))->addr = (u32)p;
    p += 0x18;

    *(u8 *)(p + 0x3) = 5;
    *(u32 *)(p + 0x4) = 0xE100008F;
    *(u8 *)(p + 0xB) = 0x64;
    *(u16 *)(p + 0x12) = 0x7940;
    *(u8 *)(p + 0x8) = *(u8 *)(p + 0x9) = *(u8 *)(p + 0xA) = 0x80;
    *(s16 *)(p + 0xC) = arg0 + 0x300;
    *(s16 *)(p + 0xE) = arg1;
    *(u8 *)(p + 0x10) = 0;
    *(u8 *)(p + 0x11) = 0;
    *(s16 *)(p + 0x14) = 0x40;
    *(s16 *)(p + 0x16) = 0x100;
    {
        u32 v = (*(u32 *)((s32)ob + (((u16)D_800B9A02) << 14)) & m24) & m24;
        u32 t = *(u32 *)p;
        t &= 0xFF000000;
        t |= v;
        *(u32 *)p = t;
    }
    ((P_TAG *)(u32 *)((s32)ob + (((u16)D_800B9A02) << 14)))->addr = (u32)p;
    p += 0x18;

    *(u8 *)(p + 0x3) = 5;
    *(u32 *)(p + 0x4) = 0xE1000086;
    *(u8 *)(p + 0xB) = 0x64;
    *(u16 *)(p + 0x12) = 0x7880;
    *(u8 *)(p + 0x8) = *(u8 *)(p + 0x9) = *(u8 *)(p + 0xA) = 0x80;
    *(s16 *)(p + 0xC) = -0xA0;
    *(s16 *)(p + 0xE) = -0x78;
    *(u8 *)(p + 0x10) = 0x20;
    *(u8 *)(p + 0x11) = 0;
    *(s16 *)(p + 0x14) = 0xA0;
    *(s16 *)(p + 0x16) = 0x100;
    {
        u32 v = (*(u32 *)((s32)ob + (((u16)D_800B9A02) << 14)) & m24) & m24;
        u32 t = *(u32 *)p;
        t &= 0xFF000000;
        t |= v;
        *(u32 *)p = t;
    }
    ((P_TAG *)(u32 *)((s32)ob + (((u16)D_800B9A02) << 14)))->addr = (u32)p;
    p += 0x18;

    *(u8 *)(p + 0x3) = 5;
    *(u32 *)(p + 0x4) = 0xE1000087;
    *(u8 *)(p + 0xB) = 0x64;
    *(u16 *)(p + 0x12) = 0x7880;
    *(u8 *)(p + 0x8) = *(u8 *)(p + 0x9) = *(u8 *)(p + 0xA) = 0x80;
    *(s16 *)(p + 0xC) = 0;
    *(s16 *)(p + 0xE) = -0x78;
    *(u8 *)(p + 0x10) = 0x40;
    *(u8 *)(p + 0x11) = 0;
    *(s16 *)(p + 0x14) = 0xA0;
    *(s16 *)(p + 0x16) = 0x100;
    {
        u32 v = (*(u32 *)((s32)ob + (((u16)D_800B9A02) << 14)) & m24) & m24;
        u32 t = *(u32 *)p;
        t &= 0xFF000000;
        t |= v;
        *(u32 *)p = t;
    }
    ((P_TAG *)(u32 *)((s32)ob + (((u16)D_800B9A02) << 14)))->addr = (u32)p;
    p += 0x18;

    D_800A5E60 = p;
}

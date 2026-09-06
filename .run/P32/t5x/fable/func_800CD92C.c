/* func_800CD92C — md_MAIN_009 (-O2). Builds six 0x18-byte SPRT-with-own-tpage prims
 * (tag / 0xE1xxxxxx draw-mode word / rgb+code 0x64 / xy / uv+clut / wh) at the
 * D_800A71D0 prim cursor and addPrim()s each onto OT word [0] of the frame's
 * ordering table D_800ABA24[D_800BAE22 * 0x1000], then republishes the advanced
 * cursor.  Four 256-wide tiles at (x-0xA0 + 0x100*i, y-0x78) plus a fixed
 * 2x(0xA0 x 0x100) backdrop.  Same-TU sibling: func_800CD674 (4 prims).
 *
 * MATCH 247/247 with ZERO register pins (P32 T5x, Fable).  The two prologue
 * mechanisms, both read from the gcc-2.7.2 source and the -dS/-dl dumps:
 *
 *  A. `m24` lands in $t1 by REF COUNT.  local_alloc orders qtys by
 *     floor_log2(n_refs)*n_refs/life with n_refs = flow's count, taken BEFORE
 *     combine (toplev.c) and never adjusted by it (combine.c:56).  The libgpu
 *     P_TAG bitfield store re-masks an already-masked getaddr() value
 *     (store_fixed_bit_field must_and), so the pre-combine RTL holds
 *     `(and (and ot m24) m24)`; combine folds it (associative rule +
 *     simplify_binary_operation op0==op1) to ONE `and`, but m24 keeps 19 refs
 *     (4*19=76) against la's 13 (3*13=39) and is allocated first -> $9.  The
 *     `(... & m24) & m24` below IS that double mask; a `register ... $9` pin is
 *     the wrong tool (it also forbids $9 to every retried allocno, cf. 501-E).
 *
 *  B. tp8D/tp8F float to the block top because the TAG LOAD is an in-place
 *     (multi-set) pseudo, exactly as the bitfield RMW expands (`t = *p;
 *     t &= FF00; t |= v; *p = t` on ONE pseudo).  sched1 splits every large
 *     constant into lui+ori (sched.c:4826, mips.md large_int) and
 *     update_n_sets makes reg_n_sets 2, so the tpage constants are unboosted
 *     pri-1 floaters; a floater is consumed only by an EMPTY ready-list cycle,
 *     and each RMW chain has one (the lhu->sll latency gap).  A single-set tag
 *     load is birthing-boosted and glued to its `and`; a multi-set one is not,
 *     and it fills those gaps instead -- so nothing eats tp8D/tp8F, they float
 *     like tp89/m24/tp8B, and local-alloc hands out $16..$19 in the target's
 *     order (tp8B < tp86 < tp8D < tp8F by life; tp87 shares $16 with tp8B).
 *     The mask temp `v` must stay a fresh expression: an in-place `v &= m24`
 *     is a 4-ref/2-insn qty that outranks `p` and steals $2 (the $v0/$v1 swap).
 *     Statement order matters once more: `v` (the OT read) BEFORE `t &= FF00`,
 *     so the FF00 constant's UID is above the index `sll` -- among two boosted
 *     insns sched1 picks the higher UID first, and with FF00 emitted early it
 *     takes prim 1's lhu->sll gap, the tag load then lingers into the store
 *     stream (memory-unit `blocking insn`), and its bubble hands tp8F's `ori`
 *     the wrong LUID (the last closeness-2 residual).
 *
 *  Kept from the t3 draft (each byte-measured there): plain `*(T *)(p + off)`
 *  field stores (a non-QImode MEM_IN_STRUCT_P varying store is exempt from
 *  conflicting with the fixed non-struct `lhu D_800BAE22`, so struct fields let
 *  the sh stores sink -- sched.c true_dependence); the OT store as an ARRAY_REF
 *  lvalue with a block-scoped `oi` (lets the final publish hop above the last
 *  OT RMW); `x -= 0xA0` on the parameter; the chained r0=g0=b0 store.
 *  D_800BAE22 must stay the TU's plain scalar: any struct/array/cast spelling
 *  goes through change_address -> memory_address -> force_reg (one shared
 *  `la`), which is not the target's 12 lui/lhu macro loads.
 */

extern u8 *D_800A71D0;
extern u32 D_800ABA24[];
extern u16 D_800BAE22;

void func_800CD92C(s32 x, s32 y, s32 c) {
    u8 *p;
    u32 m24;

    p = D_800A71D0;
    x -= 0xA0;
    y -= 0x78;

    *(u8 *)(p + 0x3) = 5;
    *(u32 *)(p + 0x4) = 0xE1000089;
    *(u8 *)(p + 0xB) = 0x64;
    *(u16 *)(p + 0x12) = 0x7840;
    *(u8 *)(p + 0x8) = *(u8 *)(p + 0x9) = *(u8 *)(p + 0xA) = c;
    *(s16 *)(p + 0xC) = x;
    *(s16 *)(p + 0xE) = y;
    *(u8 *)(p + 0x10) = 0;
    *(u8 *)(p + 0x11) = 0;
    *(s16 *)(p + 0x14) = 0x100;
    *(s16 *)(p + 0x16) = 0x100;
    m24 = 0x00FFFFFF;
    {
        u32 v = (D_800ABA24[D_800BAE22 * 0x1000] & m24) & m24;
        u32 t = *(u32 *)p;
        t &= 0xFF000000;
        t |= v;
        *(u32 *)p = t;
    }
    {
        s32 oi = D_800BAE22 * 0x1000;
        D_800ABA24[oi] = (D_800ABA24[oi] & 0xFF000000) | ((u32)p & m24);
    }
    p += 0x18;

    *(u8 *)(p + 0x3) = 5;
    *(u32 *)(p + 0x4) = 0xE100008B;
    *(u8 *)(p + 0xB) = 0x64;
    *(u16 *)(p + 0x12) = 0x7840;
    *(u8 *)(p + 0x8) = *(u8 *)(p + 0x9) = *(u8 *)(p + 0xA) = c;
    *(s16 *)(p + 0xC) = x + 0x100;
    *(s16 *)(p + 0xE) = y;
    *(u8 *)(p + 0x10) = 0;
    *(u8 *)(p + 0x11) = 0;
    *(s16 *)(p + 0x14) = 0x100;
    *(s16 *)(p + 0x16) = 0x100;
    {
        u32 v = (D_800ABA24[D_800BAE22 * 0x1000] & m24) & m24;
        u32 t = *(u32 *)p;
        t &= 0xFF000000;
        t |= v;
        *(u32 *)p = t;
    }
    {
        s32 oi = D_800BAE22 * 0x1000;
        D_800ABA24[oi] = (D_800ABA24[oi] & 0xFF000000) | ((u32)p & m24);
    }
    p += 0x18;

    *(u8 *)(p + 0x3) = 5;
    *(u32 *)(p + 0x4) = 0xE100008D;
    *(u8 *)(p + 0xB) = 0x64;
    *(u16 *)(p + 0x12) = 0x7840;
    *(u8 *)(p + 0x8) = *(u8 *)(p + 0x9) = *(u8 *)(p + 0xA) = c;
    *(s16 *)(p + 0xC) = x + 0x200;
    *(s16 *)(p + 0xE) = y;
    *(u8 *)(p + 0x10) = 0;
    *(u8 *)(p + 0x11) = 0;
    *(s16 *)(p + 0x14) = 0x100;
    *(s16 *)(p + 0x16) = 0x100;
    {
        u32 v = (D_800ABA24[D_800BAE22 * 0x1000] & m24) & m24;
        u32 t = *(u32 *)p;
        t &= 0xFF000000;
        t |= v;
        *(u32 *)p = t;
    }
    {
        s32 oi = D_800BAE22 * 0x1000;
        D_800ABA24[oi] = (D_800ABA24[oi] & 0xFF000000) | ((u32)p & m24);
    }
    p += 0x18;

    *(u8 *)(p + 0x3) = 5;
    *(u32 *)(p + 0x4) = 0xE100008F;
    *(u8 *)(p + 0xB) = 0x64;
    *(u16 *)(p + 0x12) = 0x7840;
    *(u8 *)(p + 0x8) = *(u8 *)(p + 0x9) = *(u8 *)(p + 0xA) = c;
    *(s16 *)(p + 0xC) = x + 0x300;
    *(s16 *)(p + 0xE) = y;
    *(u8 *)(p + 0x10) = 0;
    *(u8 *)(p + 0x11) = 0;
    *(s16 *)(p + 0x14) = 0x40;
    *(s16 *)(p + 0x16) = 0x100;
    {
        u32 v = (D_800ABA24[D_800BAE22 * 0x1000] & m24) & m24;
        u32 t = *(u32 *)p;
        t &= 0xFF000000;
        t |= v;
        *(u32 *)p = t;
    }
    {
        s32 oi = D_800BAE22 * 0x1000;
        D_800ABA24[oi] = (D_800ABA24[oi] & 0xFF000000) | ((u32)p & m24);
    }
    p += 0x18;

    *(u8 *)(p + 0x3) = 5;
    *(u32 *)(p + 0x4) = 0xE1000086;
    *(u8 *)(p + 0xB) = 0x64;
    *(u16 *)(p + 0x12) = 0x7880;
    *(u8 *)(p + 0x8) = *(u8 *)(p + 0x9) = *(u8 *)(p + 0xA) = c;
    *(s16 *)(p + 0xC) = -0xA0;
    *(s16 *)(p + 0xE) = -0x78;
    *(u8 *)(p + 0x10) = 0;
    *(u8 *)(p + 0x11) = 0;
    *(s16 *)(p + 0x14) = 0xA0;
    *(s16 *)(p + 0x16) = 0x100;
    {
        u32 v = (D_800ABA24[D_800BAE22 * 0x1000] & m24) & m24;
        u32 t = *(u32 *)p;
        t &= 0xFF000000;
        t |= v;
        *(u32 *)p = t;
    }
    {
        s32 oi = D_800BAE22 * 0x1000;
        D_800ABA24[oi] = (D_800ABA24[oi] & 0xFF000000) | ((u32)p & m24);
    }
    p += 0x18;

    *(u8 *)(p + 0x3) = 5;
    *(u32 *)(p + 0x4) = 0xE1000087;
    *(u8 *)(p + 0xB) = 0x64;
    *(u16 *)(p + 0x12) = 0x7880;
    *(u8 *)(p + 0x8) = *(u8 *)(p + 0x9) = *(u8 *)(p + 0xA) = c;
    *(s16 *)(p + 0xC) = 0;
    *(s16 *)(p + 0xE) = -0x78;
    *(u8 *)(p + 0x10) = 0x20;
    *(u8 *)(p + 0x11) = 0;
    *(s16 *)(p + 0x14) = 0xA0;
    *(s16 *)(p + 0x16) = 0x100;
    {
        u32 v = (D_800ABA24[D_800BAE22 * 0x1000] & m24) & m24;
        u32 t = *(u32 *)p;
        t &= 0xFF000000;
        t |= v;
        *(u32 *)p = t;
    }
    {
        s32 oi = D_800BAE22 * 0x1000;
        D_800ABA24[oi] = (D_800ABA24[oi] & 0xFF000000) | ((u32)p & m24);
    }
    p += 0x18;

    D_800A71D0 = p;
}

/* func_800CD674 - md_MAIN_009 (-O2). Builds four 0x18-byte "SPRT + own tpage"
 * primitives (a 2x2 grid of 0xA0 x 0x100 tiles, len = 5 words) at the
 * D_800A71D0 prim-buffer cursor and open-codes the PSY-Q addPrim() P_TAG
 * 24-bit RMW pair onto OT word [0] of the frame's table
 * (D_800ABA24 + D_800BAE22 * 0x4000), then republishes the advanced cursor.
 * Same family as boot's func_8001212C (-O0) and src/800.c func_80016450 (-O2).
 *
 * LEVERS (each byte-measured by removing it and re-scoring):
 *  1. THE FIELD STORES MUST BE NON-STRUCT LVALUES.  gcc-2.7.2 true_dependence
 *     drops the store->load edge when the store is MEM_IN_STRUCT_P with a
 *     varying address and mode != QImode, so with a `Sprt24 *p` struct the five
 *     `sh` stores (clut/x0/y0/w/h) SINK past the `lhu D_800BAE22` while the
 *     `sb`/`sw` ones stay -- the target's block is pure source order.  Writing
 *     every field through `*(T *)(p + off)` restores the false edge for all 13
 *     and the whole store block lands exactly.  (struct form: 102 mismatched;
 *     flat form: 6.)  Cf. cookbook 340 -- the alias oracle chooses the order.
 *  2. `p->r0 = p->g0 = p->b0 = c` chained: emits 0xA, 0x9, 0x8 (descending).
 *  3. `y + 0x100` INLINE for prims 3/4, NOT `y += 0x100`: the accumulate form
 *     gives a1's def a longer chain and sched2 hoists `addiu a1,-0x78` to the
 *     head of the prologue (16 mismatched -> 7).
 *  4. HALF1 inlines the OT address (folded lui/%lo in prim 1, register form
 *     after cse binds &D_800ABA24 in $t2); HALF2 binds it to `ot` (needed
 *     twice) -- the 800.c-lever-3 hybrid.  Binding both halves costs the
 *     $t2 materialisation; inlining both costs 3 ins/prim.
 *  5. `otv = *ot;` SPLITS the half-2 RMW so the OT read precedes the
 *     `D_800A71D0 = p` publish and the OT write follows it -- that is what puts
 *     `lui $at/sw $v0,%lo(D_800A71D0)` in the last `lw`'s shadow (7 -> 2).
 *  6. Pins: $t2/$t3 mask order needs m24/mff pinned ($9/$11); `ot` pinned adds
 *     the 5th callee-saved register (unpinned = 172 ins, frame 0x18 not 0x20);
 *     `pm` ($t0) holds prims 1-2's masked-p across prim 2's store block.
 *
 * @stuck: 2 mismatched, class REGALLOC-PERM [permuter] (sig $a3>$t1).  Prim 3's
 *   masked-p wants $a3 and prim 4's wants $t1 (m24's dying register); one
 *   shared local can only be one of them, and splitting it into two locals is
 *   +1 pseudo, which displaces `ori $s4,$s4,0x96` and the 0xE1000097 `lui $s1`
 *   (31 mismatched) in every spelling measured.  Levers measured INERT:
 *   statement order for x/y/tpr/pm (36 positions), zero-byte fences at all 70
 *   statement slots, re-ties on p/y/c/tpr/m24/mff, pm2 declared plain/register/
 *   pinned $4/$6/$7/$9, `ot` pinned to 13 different registers, arg types
 *   s16/s32/u8, `p = p + 0x18` vs `p += 0x18`, x2/y2 explicit temps,
 *   D_800A71D0 published as `p + 0x18` / before the last OT store, and
 *   -fno-schedule-insns[2] attribution (neither pass alone reproduces it).
 */

extern u8 *D_800A71D0;
extern u32 D_800ABA24[];
extern u16 D_800BAE22;

void func_800CD674(s32 x, s32 y, s32 c) {
    u8 *p;
    register u32 tp0 __asm__("$3") = 0xE1000086;
    register u32 *ot __asm__("$7");
    register u32 m24 __asm__("$9") = 0x00FFFFFF;
    register u32 mff __asm__("$11") = 0xFF000000;
    register u32 tpr __asm__("$17");
    register u32 pm __asm__("$8");
    u32 pm2;
    register u32 otv __asm__("$3");

    p = (u8 *)D_800A71D0;
    tpr = 0xE1000087;
    x -= 0xA0;
    y -= 0x78;

    *(u8  *)(p + 0x3) = 5;
    *(u32 *)(p + 0x4) = tp0;
    *(u8  *)(p + 0xB) = 0x64;
    *(u16 *)(p + 0x12) = 0x7800;
    *(u8 *)(p + 0x8) = *(u8 *)(p + 0x9) = *(u8 *)(p + 0xA) = c;
    *(s16 *)(p + 0xC) = x;
    *(s16 *)(p + 0xE) = y;
    *(u8  *)(p + 0x10) = 0;
    *(u8  *)(p + 0x11) = 0;
    *(s16 *)(p + 0x14) = 0xA0;
    *(s16 *)(p + 0x16) = 0x100;
    ot = (u32 *)((u8 *)D_800ABA24 + (D_800BAE22 << 14));
    *(u32 *)p = (*(u32 *)p & mff) | (*ot & m24);
    ot = (u32 *)((u8 *)D_800ABA24 + (D_800BAE22 << 14));
    pm = (u32)p & m24;
    otv = *ot;
    p += 0x18;
    *ot = (otv & mff) | pm;

    *(u8  *)(p + 0x3) = 5;
    *(u32 *)(p + 0x4) = tpr;
    tpr = 0xE1000097;
    *(u8  *)(p + 0xB) = 0x64;
    *(u16 *)(p + 0x12) = 0x7800;
    *(u8 *)(p + 0x8) = *(u8 *)(p + 0x9) = *(u8 *)(p + 0xA) = c;
    *(s16 *)(p + 0xC) = x + 0xA0;
    *(s16 *)(p + 0xE) = y;
    *(u8  *)(p + 0x10) = 0x20;
    *(u8  *)(p + 0x11) = 0;
    *(s16 *)(p + 0x14) = 0xA0;
    *(s16 *)(p + 0x16) = 0x100;
    ot = (u32 *)((u8 *)D_800ABA24 + (D_800BAE22 << 14));
    *(u32 *)p = (*(u32 *)p & mff) | (*ot & m24);
    ot = (u32 *)((u8 *)D_800ABA24 + (D_800BAE22 << 14));
    pm = (u32)p & m24;
    otv = *ot;
    p += 0x18;
    *ot = (otv & mff) | pm;

    *(u8  *)(p + 0x3) = 5;
    *(u32 *)(p + 0x4) = 0xE1000096;
    *(u8  *)(p + 0xB) = 0x64;
    *(u16 *)(p + 0x12) = 0x7800;
    *(u8 *)(p + 0x8) = *(u8 *)(p + 0x9) = *(u8 *)(p + 0xA) = c;
    *(s16 *)(p + 0xC) = x;
    *(s16 *)(p + 0xE) = y + 0x100;
    *(u8  *)(p + 0x10) = 0;
    *(u8  *)(p + 0x11) = 0;
    *(s16 *)(p + 0x14) = 0xA0;
    *(s16 *)(p + 0x16) = 0x100;
    ot = (u32 *)((u8 *)D_800ABA24 + (D_800BAE22 << 14));
    *(u32 *)p = (*(u32 *)p & mff) | (*ot & m24);
    ot = (u32 *)((u8 *)D_800ABA24 + (D_800BAE22 << 14));
    pm2 = (u32)p & m24;
    otv = *ot;
    p += 0x18;
    *ot = (otv & mff) | pm2;

    *(u8  *)(p + 0x3) = 5;
    *(u32 *)(p + 0x4) = tpr;
    *(u8  *)(p + 0xB) = 0x64;
    *(u16 *)(p + 0x12) = 0x7800;
    *(u8 *)(p + 0x8) = *(u8 *)(p + 0x9) = *(u8 *)(p + 0xA) = c;
    *(s16 *)(p + 0xC) = x + 0xA0;
    *(s16 *)(p + 0xE) = y + 0x100;
    *(u8  *)(p + 0x10) = 0x20;
    *(u8  *)(p + 0x11) = 0;
    *(s16 *)(p + 0x14) = 0xA0;
    *(s16 *)(p + 0x16) = 0x100;
    ot = (u32 *)((u8 *)D_800ABA24 + (D_800BAE22 << 14));
    *(u32 *)p = (*(u32 *)p & mff) | (*ot & m24);
    ot = (u32 *)((u8 *)D_800ABA24 + (D_800BAE22 << 14));

    otv = *ot;
    p += 0x18;
    D_800A71D0 = p;
    { u32 pm3 = (u32)p & m24; *ot = (otv & mff) | pm3; }
}

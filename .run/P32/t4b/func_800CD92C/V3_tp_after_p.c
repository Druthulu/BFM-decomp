/* func_800CD92C — md_MAIN_009 (-O2). Builds six 0x18-byte SPRT-with-own-tpage prims
 * (tag / 0xE1xxxxxx draw-mode word / rgb+code 0x64 / xy / uv+clut / wh) at the
 * D_800A71D0 prim cursor and addPrim()s each onto OT word [0] of the frame's
 * ordering table D_800ABA24[D_800BAE22 * 0x1000], then republishes the advanced
 * cursor.  Four 256-wide tiles at (x-0xA0 + 0x100*i, y-0x78) plus a fixed
 * 2x(0xA0 x 0x100) backdrop.  Structural sibling: func_800CD674 in this same TU
 * (4 prims, identical idiom); -O0 cousin: boot.c/func_8001212C.
 *
 * LEVERS (each measured by removing it and re-scoring):
 *  1. §364 — at -O2 the libgpu P_TAG `unsigned addr:24` bitfield is BYTE-WRONG:
 *     MEM_IN_STRUCT_P lets the oracle CSE the second D_800BAE22 load across the
 *     tag store.  The target reloads D_800BAE22 12x, so the open-coded
 *     mask/or through `*(u32 *)p` is required (src/800.c func_80016450 lever 2).
 *  2. NO STRUCT for the prim fields (the whole 245->247 unlock).  gcc-2.7.2
 *     `true_dependence` exempts a non-QImode MEM_IN_STRUCT_P ref with a VARYING
 *     address from conflicting with a non-struct ref at a CONSTANT address — so
 *     with `p->clut`/`p->x0` the `lhu D_800BAE22` floats above every halfword
 *     store and block 1's store order collapses to bytes-then-halfwords.  Plain
 *     `*(s16 *)(p + 0xC)` INDIRECT_REFs keep the dependence and hold source order.
 *     (The QImode guard is why the `sb` fields never showed the symptom.)
 *  3. The OT STORE as a genuine ARRAY_REF lvalue (`D_800ABA24[oi] = ...`, not
 *     `*ot`): the same exemption, used in the other direction — it lets the final
 *     `D_800A71D0 = p` publish hop above the last OT read-modify-write, exactly
 *     as the target schedules it.  Worth 5 instructions of ordering.
 *  4. Mutate the PARAMETERS (`x -= 0xA0`), never `sx = x - 0xA0`: with a separate
 *     local both pseudos stay live and cse re-folds `sx + 0x100` into `x + 0x60`.
 *  5. One SHORT-LIVED binding per addPrim second half (the `oi` block scope, not a
 *     function-scope `ot`): a single pseudo with 6 def/use pairs in this one huge
 *     basic block gets a dedicated register ($t8) — func_80016450 lever 3.
 *  6. `p->r0 = p->g0 = p->b0 = c` as a CHAINED assignment reproduces the reversed
 *     0xA / 0x9 / 0x8 store order (func_80016450 lever 1).
 *  7. Five §17 pins hold the callee-saved homes the target uses.  Pin-trim log
 *     (all re-scored): dropping tp8B ($16), c5 ($15) or c64 ($14) — all three
 *     inert, dropped; dropping tp8D / tp8F / tp86 — 245 ins (-2 each, one lost
 *     callee-saved); dropping tp87 — 247 ins but 104 mismatched; dropping m24
 *     ($9) — 41 mismatched.  Adding mFF ($11) or c100 ($12) is inert; adding
 *     clut ($13) is WORSE (26).
 *
 * @class: sched2 prologue weave (map §S7) — 15 mismatched, EXACT length 247/247.
 * @stuck: indices 23..246 are byte-identical and all 32 relocations were checked
 *   one-to-one against the target .s (2x2 D_800A71D0, 2x2 D_800ABA24,
 *   12x2 D_800BAE22 — same symbols, same counts).  The whole residual is one
 *   contiguous prologue window, indices 1..22: the SAME instructions in the SAME
 *   registers, with the {sw $s2, lui $s2, ori $s2} and {sw $s3, lui $s3, ori $s3}
 *   groups placed after the 9-insn `li` block instead of before it.  Root cause:
 *   in the target sched1 hoists the 0xE100008D/0xE100008F lui+ori pairs to the
 *   function top (long live range -> low local-alloc density -> callee-saved);
 *   unpinned, gcc materialises them in place and gives them $t5, so the pins
 *   reproduce the ALLOCATION but the hoist then happens in sched2, which weaves
 *   them differently (§S7: "steered by the body insns' priorities/LUIDs, not by
 *   any prologue-side lever").  Measured INERT on this residual: pin declaration
 *   order (8 permutations), assignment placement for tp8D/tp8F (6 anchors),
 *   `volatile` on D_800BAE22, `p += 0x18` vs `p = p + 0x18`, typing D_800A71D0 as
 *   `u8 *`, and every pin subset.  Measured WORSE: pinning the caller-saved
 *   constants (26), D_800BAE22 as an array (-14, cse folds the loads).
 */

extern u32 D_800A71D0;
extern u32 D_800ABA24[];
extern u16 D_800BAE22;

void func_800CD92C(s32 x, s32 y, s32 c) {
    u8 *p;
    register u32 m24 __asm__("$9");
    register u32 tp8D __asm__("$18");
    register u32 tp8F __asm__("$19");
    register u32 tp86 __asm__("$17");
    register u32 tp87 __asm__("$16");

    p = (u8 *)D_800A71D0;
    tp8D = 0xE100008D;
    tp8F = 0xE100008F;
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
    *(u32 *)p = (*(u32 *)p & 0xFF000000) | (D_800ABA24[D_800BAE22 * 0x1000] & m24);
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
    *(u32 *)p = (*(u32 *)p & 0xFF000000) | (D_800ABA24[D_800BAE22 * 0x1000] & m24);
    {
        s32 oi = D_800BAE22 * 0x1000;
        D_800ABA24[oi] = (D_800ABA24[oi] & 0xFF000000) | ((u32)p & m24);
    }
    p += 0x18;

    *(u8 *)(p + 0x3) = 5;
    *(u32 *)(p + 0x4) = tp8D;
    *(u8 *)(p + 0xB) = 0x64;
    *(u16 *)(p + 0x12) = 0x7840;
    *(u8 *)(p + 0x8) = *(u8 *)(p + 0x9) = *(u8 *)(p + 0xA) = c;
    *(s16 *)(p + 0xC) = x + 0x200;
    *(s16 *)(p + 0xE) = y;
    *(u8 *)(p + 0x10) = 0;
    *(u8 *)(p + 0x11) = 0;
    *(s16 *)(p + 0x14) = 0x100;
    *(s16 *)(p + 0x16) = 0x100;
    *(u32 *)p = (*(u32 *)p & 0xFF000000) | (D_800ABA24[D_800BAE22 * 0x1000] & m24);
    {
        s32 oi = D_800BAE22 * 0x1000;
        D_800ABA24[oi] = (D_800ABA24[oi] & 0xFF000000) | ((u32)p & m24);
    }
    p += 0x18;

    *(u8 *)(p + 0x3) = 5;
    *(u32 *)(p + 0x4) = tp8F;
    *(u8 *)(p + 0xB) = 0x64;
    *(u16 *)(p + 0x12) = 0x7840;
    *(u8 *)(p + 0x8) = *(u8 *)(p + 0x9) = *(u8 *)(p + 0xA) = c;
    *(s16 *)(p + 0xC) = x + 0x300;
    *(s16 *)(p + 0xE) = y;
    *(u8 *)(p + 0x10) = 0;
    *(u8 *)(p + 0x11) = 0;
    *(s16 *)(p + 0x14) = 0x40;
    *(s16 *)(p + 0x16) = 0x100;
    *(u32 *)p = (*(u32 *)p & 0xFF000000) | (D_800ABA24[D_800BAE22 * 0x1000] & m24);
    {
        s32 oi = D_800BAE22 * 0x1000;
        D_800ABA24[oi] = (D_800ABA24[oi] & 0xFF000000) | ((u32)p & m24);
    }
    p += 0x18;

    *(u8 *)(p + 0x3) = 5;
    tp86 = 0xE1000086;
    *(u32 *)(p + 0x4) = tp86;
    *(u8 *)(p + 0xB) = 0x64;
    *(u16 *)(p + 0x12) = 0x7880;
    *(u8 *)(p + 0x8) = *(u8 *)(p + 0x9) = *(u8 *)(p + 0xA) = c;
    *(s16 *)(p + 0xC) = -0xA0;
    *(s16 *)(p + 0xE) = -0x78;
    *(u8 *)(p + 0x10) = 0;
    *(u8 *)(p + 0x11) = 0;
    *(s16 *)(p + 0x14) = 0xA0;
    *(s16 *)(p + 0x16) = 0x100;
    *(u32 *)p = (*(u32 *)p & 0xFF000000) | (D_800ABA24[D_800BAE22 * 0x1000] & m24);
    {
        s32 oi = D_800BAE22 * 0x1000;
        D_800ABA24[oi] = (D_800ABA24[oi] & 0xFF000000) | ((u32)p & m24);
    }
    p += 0x18;

    *(u8 *)(p + 0x3) = 5;
    tp87 = 0xE1000087;
    *(u32 *)(p + 0x4) = tp87;
    *(u8 *)(p + 0xB) = 0x64;
    *(u16 *)(p + 0x12) = 0x7880;
    *(u8 *)(p + 0x8) = *(u8 *)(p + 0x9) = *(u8 *)(p + 0xA) = c;
    *(s16 *)(p + 0xC) = 0;
    *(s16 *)(p + 0xE) = -0x78;
    *(u8 *)(p + 0x10) = 0x20;
    *(u8 *)(p + 0x11) = 0;
    *(s16 *)(p + 0x14) = 0xA0;
    *(s16 *)(p + 0x16) = 0x100;
    *(u32 *)p = (*(u32 *)p & 0xFF000000) | (D_800ABA24[D_800BAE22 * 0x1000] & m24);
    {
        s32 oi = D_800BAE22 * 0x1000;
        D_800ABA24[oi] = (D_800ABA24[oi] & 0xFF000000) | ((u32)p & m24);
    }
    p += 0x18;

    D_800A71D0 = (u32)p;
}

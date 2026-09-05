/* func_800CF408 — publish four 0x18-byte "SPRT with its own tpage" primitives (a 2x2
 * 160x256 grid centred on (arg0,arg1)) at the D_800A5E60 prim cursor, addPrim()ing each
 * onto OT word D_800AA60C[frame] (D_800AA60C + gameFrame*0x4000), then republishing the
 * advanced cursor.  Same family as boot/func_8001212C (-O0) and ov_SC01_000/func_8017DD04.
 *
 * Byte-proven spellings in here (md_MAIN_007 is an -O2 TU):
 *  - the packet TAG word is a PLAIN CAST mask/or, NOT a P_TAG bitfield (§364: at -O2 the
 *    bitfield sets MEM_IN_STRUCT_P and cse then keeps the D_800B9A02 index live across the
 *    tag store — measured 163 ins vs the target's 178, -4 per block).
 *  - the OT WRITE stays a P_TAG bitfield (§351) so the trailing `D_800A5E60 = p` floats.
 *  - `(u16)D_800B9A02`, never `*(u16 *)&D_800B9A02` (§351: the ADDR_EXPR form cse's the
 *    base into a register and collapses the 8 lui/lhu pairs).
 *  - the base-split (§351): block 1 reads the OT off the raw symbol (lui $at/addu/lw %lo),
 *    then `ob = D_800AA60C` and every later reference goes through `ob`.
 *  - `arg1 += 0x100` IN PLACE inside block 2 (not `arg1 + 0x100` as an expression): the
 *    anti-dependence is what raises block 2's y0 store above its x0 store, which is the
 *    target's only x0/y0 inversion.
 *  - PINS.  `tp` ($17) makes 0xE1000087 and 0xE1000097 share one callee-saved register the
 *    way the target does; unpinned, gcc hands $s1's tail to the 0x40 constant instead and
 *    the function allocates 5 callee-saved registers (176 ins) instead of 6 (178).  `ob`
 *    ($10) fixes the $t1/$t2/$t3 rotation.  0xFFFFFF and 0x80 must NOT be pinned (§351).
 *  - `u32 pad[2]` is the +8 frame (§358: an unreferenced fixed-size aggregate is slotted).
 */
extern u8 *D_800A5E60;
extern u8 D_800AA60C[];
extern s16 D_800B9A02;

void func_800CF408(s32 arg0, s32 arg1) {
    typedef struct { u32 addr:24; u32 len:8; } P_TAG;
    u8 *p;
    register u8 *ob __asm__("$10");
    u32 mlo;
    register u32 tp __asm__("$17");
    u32 pad[2];

    p = D_800A5E60;
    arg0 -= 0xA0;

    *(u8 *)(p + 0x3) = 5;
    *(u32 *)(p + 0x4) = 0xE1000086;
    *(u8 *)(p + 0xB) = 0x64;
    *(u16 *)(p + 0x12) = 0x7980;
    *(u8 *)(p + 0xA) = 0x80;
    *(u8 *)(p + 0x9) = 0x80;
    *(u8 *)(p + 0x8) = 0x80;
    *(s16 *)(p + 0xC) = arg0;
    arg1 -= 0x78;
    *(s16 *)(p + 0xE) = arg1;
    *(u8 *)(p + 0x10) = 0x20;
    *(u8 *)(p + 0x11) = 0;
    *(s16 *)(p + 0x14) = 0xA0;
    *(s16 *)(p + 0x16) = 0x100;
    mlo = 0xFFFFFF;
    *(u32 *)p = (*(u32 *)p & 0xFF000000) | (*(u32 *)((s32)D_800AA60C + (((u16)D_800B9A02) << 14)) & mlo);
    ob = D_800AA60C;
    ((P_TAG *)((s32)ob + (((u16)D_800B9A02) << 14)))->addr = (u32)p;
    p += 0x18;

    tp = 0xE1000087;
    *(u8 *)(p + 0x3) = 5;
    *(u32 *)(p + 0x4) = tp;
    *(u8 *)(p + 0xB) = 0x64;
    *(u16 *)(p + 0x12) = 0x7980;
    *(u8 *)(p + 0xA) = 0x80;
    *(u8 *)(p + 0x9) = 0x80;
    *(u8 *)(p + 0x8) = 0x80;
    *(s16 *)(p + 0xC) = arg0 + 0xA0;
    *(s16 *)(p + 0xE) = arg1;
    arg1 += 0x100;
    *(u8 *)(p + 0x10) = 0x40;
    *(u8 *)(p + 0x11) = 0;
    *(s16 *)(p + 0x14) = 0xA0;
    *(s16 *)(p + 0x16) = 0x100;
    *(u32 *)p = (*(u32 *)p & 0xFF000000) | (*(u32 *)((s32)ob + (((u16)D_800B9A02) << 14)) & mlo);
    ((P_TAG *)((s32)ob + (((u16)D_800B9A02) << 14)))->addr = (u32)p;
    p += 0x18;

    *(u8 *)(p + 0x3) = 5;
    *(u32 *)(p + 0x4) = 0xE1000096;
    *(u8 *)(p + 0xB) = 0x64;
    *(u16 *)(p + 0x12) = 0x7980;
    *(u8 *)(p + 0xA) = 0x80;
    *(u8 *)(p + 0x9) = 0x80;
    *(u8 *)(p + 0x8) = 0x80;
    *(s16 *)(p + 0xC) = arg0;
    *(s16 *)(p + 0xE) = arg1;
    *(u8 *)(p + 0x10) = 0x20;
    *(u8 *)(p + 0x11) = 0;
    *(s16 *)(p + 0x14) = 0xA0;
    *(s16 *)(p + 0x16) = 0x100;
    *(u32 *)p = (*(u32 *)p & 0xFF000000) | (*(u32 *)((s32)ob + (((u16)D_800B9A02) << 14)) & mlo);
    ((P_TAG *)((s32)ob + (((u16)D_800B9A02) << 14)))->addr = (u32)p;
    p += 0x18;

    tp = 0xE1000097;
    *(u8 *)(p + 0x3) = 5;
    *(u32 *)(p + 0x4) = tp;
    *(u8 *)(p + 0xB) = 0x64;
    *(u16 *)(p + 0x12) = 0x7980;
    *(u8 *)(p + 0xA) = 0x80;
    *(u8 *)(p + 0x9) = 0x80;
    *(u8 *)(p + 0x8) = 0x80;
    *(s16 *)(p + 0xC) = arg0 + 0xA0;
    *(s16 *)(p + 0xE) = arg1;
    *(u8 *)(p + 0x10) = 0x40;
    *(u8 *)(p + 0x11) = 0;
    *(s16 *)(p + 0x14) = 0xA0;
    *(s16 *)(p + 0x16) = 0x100;
    *(u32 *)p = (*(u32 *)p & 0xFF000000) | (*(u32 *)((s32)ob + (((u16)D_800B9A02) << 14)) & mlo);
    ((P_TAG *)((s32)ob + (((u16)D_800B9A02) << 14)))->addr = (u32)p;
    p += 0x18;

    D_800A5E60 = p;
}

void func_8017F694(s32 arg0) {
    /* Frame lever (cookbook "frame-pad induction"): the target's frame is
       0x20 with $ra at 0x18, i.e. vars=8 with nothing $sp-addressed.  A
       declared BLKmode local reserves its 8-byte slot at expand and -O2 DCE
       never reclaims it; `(void)&x` escapes the address with zero code and
       silences -Wunused.  Without it: frame 0x18 / $ra at 0x10 (4 diffs). */
    SVec8_8017F694 unused;
    (void)&unused;

    if (D_8019F9FC != NULL) {
        if (*(s32 *)(*(s32 *)(arg0 + 0x20) + 0x4) < 0) {
            *(s32 *)((u8 *)D_8019F9FC + 0x4) |= 0x80000000;
        } else {
            u8 *ptr2 = (u8 *)D_8019F9FC;
            /* §194-A zero-byte fence at the HEAD of the else-arm block.
               Two jobs, both load-bearing:
                 1. reorg.c refuses to put an ASM insn in a delay slot, so the
                    bgez's eager steal cannot take this arm's `lui 0x7FFF` --
                    it falls back to the fall-through arm's `lui 0x80000000`,
                    which is what the target's delay slot holds.
                 2. it pins the arm's first sched1 group, giving the target's
                    lui / lw / ori / sh / and order.
               Drop it and the diff is 7 (stolen 0x7FFF lui + shuffled arm). */
            *(s32 *)(ptr2 + 0x4) &= 0x7FFFFFFF;
            *(s16 *)(ptr2 + 0x10) = 0;
            *(u16 *)(ptr2 + 0x12) = *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x12);
            *(s16 *)(ptr2 + 0x14) = 0;
            /* four separate `lw 0x20($t0)` intervals in the target: each
               statement re-reads the pointer (§193-E), so never cache it. */
            *(SVec8_8017F694 *)(ptr2 + 0x8) = *(SVec8_8017F694 *)(*(s32 *)(arg0 + 0x20) + 0x8);
            *(SVec8_8017F694 *)(ptr2 + 0x18) = *(SVec8_8017F694 *)(*(s32 *)(arg0 + 0x20) + 0x18);
            func_800183E0((s32)(D_80188FAC + ((D_800B99DA & 7) << 5)));
        }
    }
}

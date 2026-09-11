void func_8017F438(s32 param_1) {
    u8 *s0 = (u8 *)param_1;
    s32 t1;
    s32 t2;
    s32 p;

    t1 = *(s16 *)(s0 + 6);
    t2 = *(s16 *)(s0 + 0xA);
    if (t1 * t1 + (t2 + 0x482) * (t2 + 0x482) > 0x1323F) {
        func_8012ADE4(param_1);
        *(s32 *)(s0 + 0x14) = 0;
    }

    func_8002D4C8(0xB32, 0);

    if (*(u16 *)s0 != 0) {
        /* Copy the model's position/rotation into both attached objects and mirror the model's bit 31 into theirs.
         * The bit is TESTED with the mask (not `< 0`): the mask register is loaded before the branch, cse reuses it
         * for the `|=` (so the store's constant sits in the branch delay slot), and combine's sign test leaves a
         * `(use)` of the dead AND result that reload gives a stack slot — the frame's 16 bytes (P36 S104 e26). */
        p = *(s32 *)(s0 + 0xCC);
        *(u16 *)(p + 0x8) = *(u16 *)(s0 + 0x6);
        *(u16 *)(p + 0xA) = *(u16 *)(s0 + 0xA);
        *(u16 *)(p + 0xC) = *(u16 *)(s0 + 0xE);
        *(u16 *)(p + 0x10) = *(u16 *)(*(s32 *)(s0 + 0x20) + 0x10);
        *(u16 *)(p + 0x12) = *(u16 *)(*(s32 *)(s0 + 0x20) + 0x12) + *(u16 *)(s0 + 0xFC);
        *(u16 *)(p + 0x14) = *(u16 *)(*(s32 *)(s0 + 0x20) + 0x14);
        if (*(u32 *)(*(s32 *)(s0 + 0x20) + 4) & 0x80000000) {
            *(u32 *)(p + 4) |= 0x80000000;
        } else {
            *(u32 *)(p + 4) &= 0x7FFFFFFF;
        }

        p = *(s32 *)(s0 + 0xD0);
        *(u16 *)(p + 0x8) = *(u16 *)(s0 + 0x6);
        *(u16 *)(p + 0xA) = *(u16 *)(s0 + 0xA);
        *(u16 *)(p + 0xC) = *(u16 *)(s0 + 0xE);
        *(u16 *)(p + 0x10) = *(u16 *)(*(s32 *)(s0 + 0x20) + 0x10);
        *(u16 *)(p + 0x12) = *(u16 *)(*(s32 *)(s0 + 0x20) + 0x12) + *(u16 *)(s0 + 0xFE);
        *(u16 *)(p + 0x14) = *(u16 *)(*(s32 *)(s0 + 0x20) + 0x14);
        if (*(u32 *)(*(s32 *)(s0 + 0x20) + 4) & 0x80000000) {
            *(u32 *)(p + 4) |= 0x80000000;
        } else {
            *(u32 *)(p + 4) &= 0x7FFFFFFF;
        }
    }
}

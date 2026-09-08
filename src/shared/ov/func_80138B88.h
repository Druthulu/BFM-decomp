/* func_80138B88 — shared body (overlay slot 0x80128158, h_exact 93b82718). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_80138B88(s32 a0) {
    s32 a1;
    if (*(s32*)(a0 + 0x8) & 0x2000) {
        *(s16*)(a0 + 0x4) = 0xD;
    } else {
        *(s16*)(a0 + 0x4) = 0xC;
        *(s32*)(a0 + 0x8) &= ~0x1000;
        a1 = *(s32*)(a0 + 0x40);
        if (a1 != 0) {
            if (*(u16*)(a0 + 0x18) != 0) {
                *(s16*)a1 = 3;
            }
        }
    }
}

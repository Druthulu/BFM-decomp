/* func_80150B28 — shared body (overlay slot 0x80128158, h_exact 74650617). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_80150B28(int param_1) {

    extern s32 D_800AE6B0;
    extern void (*D_80180740[])(void);
    u32 idx;
    u32 sub;

    if ((D_800AE6B0 & 0x80FFFFFF) == 0) {
        idx = *(u16 *)(param_1 + 0x16C);
        if (idx != 0 && idx < 0x26) {
            sub = idx - 1;
            D_80180740[sub]();
        }
    }
    *(u16 *)(param_1 + 0x16C) = 0;
}

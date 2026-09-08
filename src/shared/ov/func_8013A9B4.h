/* func_8013A9B4 — shared body (overlay slot 0x80128158, h_exact 694d6dd6). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8013A9F8(s32 a0, s32 a1);
void func_8013A9B4(s32 a0, s32 a1) {
    *(s16 *)(a1 + 0x2) = 0;
    *(s32 *)(a1 + 0x4) = a0;
    *(s32 *)(a0 + 0x40) = a1;
    *(s16 *)(a1 + 0x0) = 1;
    *(s16 *)(a1 + 0xC) = 0;
    *(s16 *)(a1 + 0xE) = 0;
    func_8013A9F8(a1, *(u16 *)(a0 + 0x18));
}

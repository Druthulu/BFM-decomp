/* func_80138D58 — shared body (overlay slot 0x80128158, h_exact 9e12464b). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8013A9F8(s32 a0, s32 a1);
void func_80138D58(s32 a0, u16 a1) {
    if (*(s32 *)(a0 + 0x40) == 0) {
        return;
    }
    if ((u32)(*(u16 *)(a0 + 0x18) - 2) >= 5) {
        return;
    }
    if ((u32)(u16)(a1 - 2) >= 5) {
        return;
    }
    *(s16 *)(a0 + 0x18) = a1;
    func_8013A9F8(*(s32 *)(a0 + 0x40), a1);
}

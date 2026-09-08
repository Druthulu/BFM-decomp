/* func_8016E728 — shared body (overlay slot 0x80128158, h_exact 89a42c5c). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80146C3C();
extern void func_8016E778();
void func_8016E728(u8 *a0) {
    s32 v0;
    s32 v1;
    v0 = (u16)*(u16 *)(a0 + 0x12) + 0x400;
    v1 = (u16)*(u16 *)(a0 + 0x16) - 8;
    *(u16 *)(a0 + 0x12) = v0;
    *(u16 *)(a0 + 0x16) = v1;
    if ((s16)v1 <= 0) {
        func_80146C3C();
    } else {
        func_8016E778();
    }
}

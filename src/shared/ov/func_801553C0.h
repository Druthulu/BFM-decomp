/* func_801553C0 — shared body (overlay slot 0x80128158, h_exact 6459cdbf). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80029178(s32);
extern void func_8001D150(s32, s32);
void func_801553C0(s32 a0) {
    s32 *flags;
    flags = (s32 *)(a0 + 0x44);
    if ((*flags & 4) != 0 || (func_80029178(0x12F) & 0xFF) != 0) {
        *flags = *flags & 0xEFFFFFFF;
    } else {
        *flags = *flags | 0x10000000;
    }
    func_8001D150(*(s32 *)(*(s32 *)(a0 + 0x20) + 0x24), 0x15);
}

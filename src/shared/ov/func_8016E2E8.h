/* func_8016E2E8 — shared body (overlay slot 0x80128158, h_exact 0f87b8a6). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8016E3CC(s32 a0);
extern void func_80146C3C();
void func_8016E2E8(void *a0) {
    s32 *s1 = *(s32 **)((s32)a0 + 0x20);
    func_8016E3CC((s32)a0);
    if (--*(s32 *)((s32)a0 + 0x1C) != 0) {
        *(u16 *)((s32)s1 + 0x18) -= 0x100;
        *(u16 *)((s32)s1 + 0x1A) -= 0x120;
    } else {
        ((void (*)(s32))func_80146C3C)((s32)a0);
    }
}

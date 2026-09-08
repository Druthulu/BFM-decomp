/* func_801684B4 — shared body (overlay slot 0x80128158, h_exact fbef0f0b). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80146C3C();
extern s32 func_80166994(s32 a0, s32 a1, s32 a2, s32 a3);
void func_801684B4(s32 a0) {
    if ((*(s32 *)(*(s32 *)(a0 + 0x34) + 0x44) & 0x2) == 0) {
        func_80146C3C();
    } else {
        s16 v0 = *(u16 *)(a0 + 0x2A) - 1;
        *(s16 *)(a0 + 0x2A) = v0;
        if (v0 == 0) {
            func_80166994(a0, 0, 2, 0);
            *(s16 *)(a0 + 0x2) = *(u16 *)(a0 + 0x2) + 1;
        }
    }
}

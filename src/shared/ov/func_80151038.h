/* func_80151038 — shared body (overlay slot 0x80128158, h_exact 44a05e1d). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80151184(s32 a0, s32 a1, s32 a2);
extern s16 currentLocationId;
void func_80151038(s32 a0) {
    s32 a2 = 0x18;
    if (currentLocationId == 0x30A0) {
        a2 = 0x30;
    }
    func_80151184(a0, 0xC00C, a2);
}

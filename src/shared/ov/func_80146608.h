/* func_80146608 — shared body (overlay slot 0x80128158, h_exact 1580ccd0). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_801466F0(s32 a0, s32 a1, s32 a2, s32 a3, s32 sp5, s32 sp6, s32 sp7, s32 sp8);
extern s32 D_8011F9D0;
s32 func_80146608(s32 a0, s32 a1, s32 a2, s32 a3, s16 arg9, s32 arg10, s32 arg11, s32 arg12, s32 arg13) {
    u8 *p;
    u8 *end;
    s32 cnt;
    cnt = 0;
    p = (u8 *)&D_8011F9D0;
    end = p + 0x820;
    while (p < end) {
        if (*(u16 *)p == (a0 & 0xFFFF)) {
            cnt++;
        }
        p += 0x68;
    }
    if ((u32)cnt >= (u32)arg12) {
        return 0;
    }
    func_801466F0(a0 & 0xFFFF, a1, (s16)a2, (s16)a3, arg9, arg10, arg11, arg13);
}

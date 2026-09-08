/* func_8012E504 — shared body (overlay slot 0x80128158, h_exact 71744d84). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 D_801202A0[];
s32 func_8012E504(s32 a0, s32 a1) {
    s32 p;
    s32 end;
    p = (s32)D_801202A0;
    end = (s32)D_801202A0 + 0x6480;
    for (; p != end; p += 0x10C) {
        if (p != a0) {
            if (*(u16*)p == a1) {
                return p;
            }
        }
    }
    return 0;
}

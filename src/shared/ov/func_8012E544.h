/* func_8012E544 — shared body (overlay slot 0x80128158, h_exact f280934f). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 D_801202A0[];
s32 func_8012E544(s32 a0) {
    s32 a1;
    s32 v1;
    v1 = (s32)D_801202A0;
    a1 = v1 + 0x6480;
    if (v1 != a1) {
        do {
            if (*(u16 *)v1 == a0) {
                return v1;
            }
            v1 += 0x10C;
        } while (v1 != a1);
    }
    return 0;
}

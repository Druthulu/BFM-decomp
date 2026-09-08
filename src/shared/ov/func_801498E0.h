/* func_801498E0 — shared body (overlay slot 0x80128158, h_exact c7fd0d93). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80149AA8(s32 *a0);
extern s32 func_80149B54(s32 *a0);
extern u16 *func_80146750(u16 *param_1);
s32 func_801498E0(s32 *a0) {
    s16 st[4];
    s32 stw[3];
    if (func_80149AA8(a0) != 0 || func_80149B54(a0) != 0) {
        st[0] = 8;
        stw[0] = (s32)a0;
        st[1] = 0;
        st[2] = -0x1E;
        st[3] = 0;
        stw[1] = 0;
        stw[2] = 0;
        func_80146750(st);
        return 1;
    }
    return 0;
}

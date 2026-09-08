/* func_80149A64 — shared body (overlay slot 0x80128158, h_exact 0b8da7ea). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80149AA8(s32 *a0);
extern s32 func_80149B54(s32 *a0);
s32 func_80149A64(s32 *a0) {
    if (func_80149AA8(a0) || func_80149B54(a0)) {
        return 1;
    }
    return 0;
}
